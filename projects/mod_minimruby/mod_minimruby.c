#include "http_config.h"
module AP_MODULE_DECLARE_DATA minimruby_module;

typedef struct minim_config {
  unsigned int mimim_enabled;
} minim_config_t;

typedef struct minim_dir_config {
  char *mimim_handler_code;
} minim_dir_config_t;

static void *minim_create_dir_config(apr_pool_t *p, char *_dirname)
{
  minim_dir_config_t *conf = (minim_dir_config_t *)apr_pcalloc(p, sizeof(minim_dir_config_t));
  conf->minim_handler_code = NULL;
  return conf;
}

static void *minim_create_config(apr_pool_t *p, server_rec *server)
{
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
  minimi_config_t *dir_conf = (minim_config_t *)mconfig;
  dir_conf->minim_handler_code = apr_pcalloc(cmd->pool, sizeof(strlen(arg)));
  strncpy(dir_conf->minim_handler_code, arg, strlen(arg));
  return NULL;
}

static int mod_mruby_handler_inline(request_rec *r) {
  minimi_config_t *dir_conf = ap_get_module_config(r->per_dir_config, &minimruby_module);
  if (!dir_conf->minim_handler_code)
    return DECLINED;

  ap_set_content_type(r, "text/plain");
  ap_rprintf("My First Apache Module!\n");
  ap_rprintf("Code: %s\n", dir_conf->minim_handler_code);

  return OK;
}

static const command_rec module_cmds[] =
  {
   AP_INIT_FLAG("miniMrubyEnable", set_minim_handler_enable
                NULL, RSRC_CONF | ACCESS_CONF, "Sample handler"),
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
