/*
** mrb_filestat.c - FileStat class
**
** Copyright (c) Uchio Kondo 2020
**
** See Copyright Notice in LICENSE
*/

#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/error.h>
#include <mruby/string.h>
#include <mruby/variable.h>

//#include <mruby/class.h> // for MRB_TT*

#include "mrb_filestat.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  struct stat* stat;
} mrb_filestat_data;

static const struct mrb_data_type mrb_filestat_data_type = {
  "mrb_filestat_data", mrb_free,
};

static mrb_value mrb_filestat_init(mrb_state *mrb, mrb_value self)
{
  mrb_filestat_data *data;
  mrb_value pathname;
  int ret;

  data = (mrb_filestat_data *)DATA_PTR(self);
  if (data) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "cannot call intialize more than once");
  }
  DATA_TYPE(self) = &mrb_filestat_data_type;

  mrb_get_args(mrb, "S", &pathname);
  data = (mrb_filestat_data *)mrb_malloc(mrb, sizeof(mrb_filestat_data));
  data->stat = mrb_malloc(mrb, sizeof(struct stat));
  ret = stat(mrb_string_cstr(mrb, pathname), data->stat);
  if (ret == -1) {
    mrb_sys_fail(mrb, "stat failed");
  }

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@pathname"), pathname);
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_filestat_size(mrb_state *mrb, mrb_value self)
{
  mrb_filestat_data *data = DATA_PTR(self);

  return mrb_fixnum_value(data->stat->st_size);
}

static mrb_value mrb_filestat_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_file_stat_gem_init(mrb_state *mrb)
{
  struct RClass *file, *filestat;
  file = mrb_class_get(mrb, "File");
  filestat = mrb_define_class_under(mrb, file, "Stat", mrb->object_class);
  mrb_define_method(mrb, filestat, "initialize", mrb_filestat_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, filestat, "size", mrb_filestat_size, MRB_ARGS_NONE());

  //MRB_SET_INSTANCE_TT(filestat, MRB_TT_DATA);

  DONE;
}

void mrb_mruby_file_stat_gem_final(mrb_state *mrb)
{
}
