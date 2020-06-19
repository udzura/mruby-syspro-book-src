/*
** mrb_filestat.c - FileStat class
**
** Copyright (c) Uchio Kondo 2020
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_filestat.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  mrb_int len;
} mrb_filestat_data;

static const struct mrb_data_type mrb_filestat_data_type = {
  "mrb_filestat_data", mrb_free,
};

static mrb_value mrb_filestat_init(mrb_state *mrb, mrb_value self)
{
  mrb_filestat_data *data;
  char *str;
  mrb_int len;

  data = (mrb_filestat_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_filestat_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_filestat_data *)mrb_malloc(mrb, sizeof(mrb_filestat_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_filestat_hello(mrb_state *mrb, mrb_value self)
{
  mrb_filestat_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_filestat_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_file_stat_gem_init(mrb_state *mrb)
{
  struct RClass *filestat;
  filestat = mrb_define_class(mrb, "FileStat", mrb->object_class);
  mrb_define_method(mrb, filestat, "initialize", mrb_filestat_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, filestat, "hello", mrb_filestat_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, filestat, "hi", mrb_filestat_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_file_stat_gem_final(mrb_state *mrb)
{
}

