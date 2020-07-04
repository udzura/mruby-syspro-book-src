#include <mruby.h>
#include <mruby/string.h>

#define CORE_PRIVATE
#include "httpd.h"
#include "apr_strings.h"
#include "http_protocol.h"
#include "http_log.h"

#include "mod_minimruby.h"

request_rec *minim_request_rec = NULL;

void minim_push_request(request_rec *r)
{
  minim_request_rec = r;
}

static request_rec *minim_get_request(void)
{
  return minim_request_rec;
}

void minim_clear_request(void)
{
  minim_request_rec = NULL;
}

static mrb_value minim_ap_str_or_nil_value(mrb_state *mrb, apr_pool_t *p, const char* value)
{
  const char *val;

  if (value == NULL) {
    return mrb_nil_value();
  }
  val = apr_pstrdup(p, value);
  return mrb_str_new_cstr(mrb, val);
}

static mrb_value minim_get_request_body(mrb_state *mrb, mrb_value self)
{
  char *val;
  int len;
  request_rec *r = minim_get_request();
  if (r->method_number == M_POST ||
      r->method_number == M_PUT ||
      r->method_number == M_PATCH) {
    ap_setup_client_block(r, REQUEST_CHUNKED_ERROR);
    len = r->remaining;
    val = apr_pcalloc(r->pool, len);
    ap_should_client_block(r);
    ap_get_client_block(r, val, len);
    return mrb_str_new(mrb, val, len);
  }
  return mrb_nil_value();
}

static mrb_value minim_get_request_args(mrb_state *mrb, mrb_value self)
{
  request_rec *r = minim_get_request();
  return minim_ap_str_or_nil_value(mrb, r->pool, r->args);
}

static mrb_value minim_get_request_unparsed_uri(mrb_state *mrb, mrb_value self)
{
  request_rec *r = minim_get_request();
  return minim_ap_str_or_nil_value(mrb, r->pool, r->unparsed_uri);
}

static mrb_value minim_get_request_uri(mrb_state *mrb, mrb_value self)
{
  request_rec *r = minim_get_request();
  return minim_ap_str_or_nil_value(mrb, r->pool, r->uri);
}

static mrb_value minim_get_request_path_info(mrb_state *mrb, mrb_value self)
{
  request_rec *r = minim_get_request();
  return minim_ap_str_or_nil_value(mrb, r->pool, r->path_info);
}

static mrb_value minim_get_request_content_type(mrb_state *mrb, mrb_value self)
{
  request_rec *r = minim_get_request();
  return minim_ap_str_or_nil_value(mrb, r->pool, r->content_type);
}

static mrb_value minim_get_request_method(mrb_state *mrb, mrb_value self)
{
  request_rec *r = minim_get_request();
  return minim_ap_str_or_nil_value(mrb, r->pool, r->method);
}

static mrb_value minim_get_request_hostname(mrb_state *mrb, mrb_value self)
{
  request_rec *r = minim_get_request();
  return minim_ap_str_or_nil_value(mrb, r->pool, r->hostname);
}

static mrb_value minim_set_request_content_type(mrb_state *mrb, mrb_value self)
{
  mrb_value val;
  request_rec *r = minim_get_request();
  mrb_get_args(mrb, "S", &val);

  ap_set_content_type(r, mrb_string_cstr(mrb, val));
  return val;
}

static mrb_value minim_request_rprint(mrb_state *mrb, mrb_value self)
{
  char *val;
  request_rec *r = minim_get_request();
  mrb_get_args(mrb, "z", &val);

  ap_rprintf(r, "%s", val);
  return mrb_nil_value();
}

static mrb_value minim_log_error(mrb_state *mrb, mrb_value self)
{
  char *val;
  int level;
  request_rec *r = minim_get_request();
  mrb_get_args(mrb, "iz", &level, &val);
  ap_log_error(APLOG_MARK, level, 0, r->server, "%s", val);

  return mrb_nil_value();
}

void mrb_minim_request_gem_init(mrb_state *mrb)
{
  struct RClass *req;
  req = mrb_define_class(mrb, "Request", mrb->object_class);
  mrb_define_method(mrb, req, "body", minim_get_request_body, MRB_ARGS_NONE());
  mrb_define_method(mrb, req, "unparsed_uri", minim_get_request_unparsed_uri, MRB_ARGS_NONE());
  mrb_define_method(mrb, req, "uri", minim_get_request_uri, MRB_ARGS_NONE());
  mrb_define_method(mrb, req, "path_info", minim_get_request_path_info, MRB_ARGS_NONE());
  mrb_define_method(mrb, req, "args", minim_get_request_args, MRB_ARGS_NONE());
  mrb_define_method(mrb, req, "content_type", minim_get_request_content_type, MRB_ARGS_NONE());
  mrb_define_method(mrb, req, "method", minim_get_request_method, MRB_ARGS_NONE());
  mrb_define_method(mrb, req, "hostname", minim_get_request_hostname, MRB_ARGS_NONE());

  mrb_define_method(mrb, req, "content_type=", minim_set_request_content_type, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, req, "rprint", minim_request_rprint, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, req, "log", minim_log_error, MRB_ARGS_REQ(2));

  //mrb_define_const(mrb, req, "APLOG_EMERG", mrb_fixnum_value(APLOG_EMERG));
#define DEFINE_LOGLEVEL(name) \
  mrb_define_const(mrb, req, #name, mrb_fixnum_value(name))

  DEFINE_LOGLEVEL(APLOG_EMERG);
  DEFINE_LOGLEVEL(APLOG_ALERT);
  DEFINE_LOGLEVEL(APLOG_CRIT);
  DEFINE_LOGLEVEL(APLOG_ERR);
  DEFINE_LOGLEVEL(APLOG_WARNING);
  DEFINE_LOGLEVEL(APLOG_NOTICE);
  DEFINE_LOGLEVEL(APLOG_INFO);
  DEFINE_LOGLEVEL(APLOG_DEBUG);
}
