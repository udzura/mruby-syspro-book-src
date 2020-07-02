#define CORE_PRIVATE
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "http_log.h"
#include "apr_thread_proc.h"

apr_thread_mutex_t *minim_mutex;

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

void mrb_minim_request_gem_init(mrb_state *mrb);

module AP_MODULE_DECLARE_DATA minimruby_module;

typedef struct minim_config {
  unsigned int minim_enabled;
} minim_config_t;

typedef struct minim_dir_config {
  char *minim_handler_code;
} minim_dir_config_t;

static void *minim_create_dir_config(apr_pool_t *p, char *_dirname)
{
  minim_dir_config_t *conf = (minim_dir_config_t *)apr_pcalloc(p, sizeof(minim_dir_config_t));
  conf->minim_handler_code = NULL;
  return conf;
}

static void *minim_create_config(apr_pool_t *p, server_rec *server)
{
  // TODO be worker initial hook
  apr_status_t status = apr_thread_mutex_create(&minim_mutex, APR_THREAD_MUTEX_DEFAULT, p);
  if (status != APR_SUCCESS) {
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(05001) "Error creating thread mutex.");
    return NULL;
  }
  minim_config_t *conf = (minim_config_t *)apr_pcalloc(p, sizeof(minim_config_t));
  conf->minim_enabled = 0;
  return conf;
}

static const char *set_minim_handler_enable(cmd_parms *cmd, void *mconfig, int flag)
{
  minim_config_t *conf =
    (minim_config_t *)ap_get_module_config(cmd->server->module_config, &minimruby_module);
  conf->minim_enabled = flag;
  return NULL;
}

static const char *set_minim_handler_inline(cmd_parms * cmd, void *mconfig, const char *arg)
{
  #define CODE_MAX 32768
  minim_dir_config_t *dir_conf = (minim_dir_config_t *)mconfig;
  size_t len = (size_t)strlen(arg) + 1;
  if (len > CODE_MAX)
    len = CODE_MAX;

  dir_conf->minim_handler_code = apr_pcalloc(cmd->pool, len);
  strncpy(dir_conf->minim_handler_code, arg, len);
  return NULL;
}

int minim_push_request(request_rec *r);
void minim_clear_request(void);

static int mod_mruby_handler_inline(request_rec *r) {
  minim_dir_config_t *dir_conf = ap_get_module_config(r->per_dir_config, &minimruby_module);
  minim_config_t *conf = ap_get_module_config(r->server->module_config, &minimruby_module);
  if (!conf->minim_enabled)
    return DECLINED;
  if (!dir_conf->minim_handler_code)
    return DECLINED;

  if (apr_thread_mutex_lock(minim_mutex) != APR_SUCCESS) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "mutex failed");
    return HTTP_INTERNAL_SERVER_ERROR;
  }

  (void)minim_push_request(r);

  ap_set_content_type(r, "text/plain");

  mrb_state *mrb = mrb_open();
  mrb_value v;
  mrb_minim_request_gem_init(mrb);

  v = mrb_load_string(mrb, dir_conf->minim_handler_code);
  if (mrb->exc) {
    ap_rprintf(r, "!!! mruby raised an error:\n");
    ap_rprintf(
               r, "%s",
               mrb_string_cstr(mrb, mrb_inspect(mrb, mrb_obj_value(mrb->exc)))
               );
    ap_rprintf(r, "\n");
    r->status = HTTP_INTERNAL_SERVER_ERROR;
    mrb_close(mrb);
    return OK;
  }

  /* ap_rprintf(r, "My First Apache Module!\n"); */
  /* ap_rprintf(r, "Code: %s\n", dir_conf->minim_handler_code); */
  const char *ret;
  if (mrb_string_p(v)) {
    ret = mrb_string_cstr(mrb, v);
  } else {
    ret = mrb_string_cstr(mrb, mrb_inspect(mrb, v));
  }
  ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, r->server, "return value is: %s", ret);

  minim_clear_request();
  if (apr_thread_mutex_unlock(minim_mutex) != APR_SUCCESS) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "mutex unlock failed");
    return HTTP_INTERNAL_SERVER_ERROR;
  }
  mrb_close(mrb);
  return OK;
}

static const command_rec module_cmds[] =
  {
   AP_INIT_FLAG("miniMrubyEnable", set_minim_handler_enable,
                NULL, RSRC_CONF | ACCESS_CONF, "Sample handler"),
   AP_INIT_TAKE1("miniMrubyCode", set_minim_handler_inline,
                NULL, RSRC_CONF | ACCESS_CONF, "Sample handler code"),
   { NULL },
  };

static void register_hooks(apr_pool_t *p)
{
  ap_hook_handler(mod_mruby_handler_inline, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA minimruby_module =
  {
    STANDARD20_MODULE_STUFF,
    minim_create_dir_config,
    NULL,
    minim_create_config,
    NULL,
    module_cmds,
    register_hooks
  };
