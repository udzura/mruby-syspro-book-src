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
#include <sys/sysmacros.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/error.h>
#include <mruby/string.h>
#include <mruby/value.h>
#include <mruby/variable.h>

#include "mrb_filestat.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  struct stat* stat;
} mrb_filestat_data;

void mrb_filestat_free(mrb_state *mrb, void *p)
{
  mrb_filestat_data *data = (mrb_filestat_data *)p;
  mrb_free(mrb, data->stat);
  mrb_free(mrb, data);
}

static const struct mrb_data_type mrb_filestat_data_type = {
  "mrb_filestat_data", mrb_filestat_free,
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

  return mrb_fixnum_value((mrb_int)data->stat->st_size);
}

static mrb_value mrb_filestat_ino(mrb_state *mrb, mrb_value self)
{
  mrb_filestat_data *data = DATA_PTR(self);

  return mrb_fixnum_value((mrb_int)data->stat->st_ino);
}

static mrb_value mrb_filestat_uid(mrb_state *mrb, mrb_value self)
{
  mrb_filestat_data *data = DATA_PTR(self);

  return mrb_fixnum_value((mrb_int)data->stat->st_uid);
}

static mrb_value mrb_filestat_gid(mrb_state *mrb, mrb_value self)
{
  mrb_filestat_data *data = DATA_PTR(self);

  return mrb_fixnum_value((mrb_int)data->stat->st_gid);
}

#define MRB_EXTRACT_DEV(obj, dev)                     \
  ((mrb_filestat_data *)DATA_PTR(obj))->stat->st_ ##dev

static mrb_value mrb_filestat_dev_major(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(major(MRB_EXTRACT_DEV(self, dev)));
}

static mrb_value mrb_filestat_dev_minor(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(minor(MRB_EXTRACT_DEV(self, dev)));
}

static mrb_value mrb_filestat_rdev_major(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(major(MRB_EXTRACT_DEV(self, rdev)));
}

static mrb_value mrb_filestat_rdev_minor(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(minor(MRB_EXTRACT_DEV(self, rdev)));
}

#define MRB_EXTRACT_MODE(obj) \
  ((mrb_filestat_data *)DATA_PTR(obj))->stat->st_mode

static mrb_value mrb_filestat_mode(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(MRB_EXTRACT_MODE(self));
}

static mrb_value mrb_filestat_is_file(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value((mrb_bool)S_ISREG(MRB_EXTRACT_MODE(self)));
}

static mrb_value mrb_filestat_is_dir(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value((mrb_bool)S_ISDIR(MRB_EXTRACT_MODE(self)));
}

#define MRB_EXTRACT_TIME(obj, tim) \
  ((mrb_filestat_data *)DATA_PTR(obj))->stat->st_ ##tim

static mrb_value mrb_filestat_mtime(mrb_state *mrb, mrb_value self)
{
  struct timespec mtime = MRB_EXTRACT_TIME(self, mtim);
  mrb_int sec = mtime.tv_sec;
  mrb_int usec = (mrb_int)(mtime.tv_nsec / 1000);
  mrb_value ret;
  struct RClass *time = mrb_class_get(mrb, "Time");
  ret = mrb_funcall(mrb, mrb_obj_value(time), "at",
                    2, mrb_fixnum_value(sec), mrb_fixnum_value(usec));

  return ret;
}

void mrb_mruby_file_stat_gem_init(mrb_state *mrb)
{
  struct RClass *file, *filestat;
  file = mrb_class_get(mrb, "File");
  filestat = mrb_define_class_under(mrb, file, "Stat", mrb->object_class);
  mrb_define_method(mrb, filestat, "initialize", mrb_filestat_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, filestat, "size", mrb_filestat_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "inode", mrb_filestat_ino, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "uid", mrb_filestat_uid, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "gid", mrb_filestat_gid, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "dev_major", mrb_filestat_dev_major, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "dev_minor", mrb_filestat_dev_minor, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "rdev_major", mrb_filestat_rdev_major, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "rdev_minor", mrb_filestat_rdev_minor, MRB_ARGS_NONE());

  mrb_define_method(mrb, filestat, "mode", mrb_filestat_mode, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "file?", mrb_filestat_is_file, MRB_ARGS_NONE());
  mrb_define_method(mrb, filestat, "directory?", mrb_filestat_is_dir, MRB_ARGS_NONE());

  mrb_define_method(mrb, filestat, "mtime", mrb_filestat_mtime, MRB_ARGS_NONE());

  MRB_SET_INSTANCE_TT(filestat, MRB_TT_DATA);

  DONE;
}

void mrb_mruby_file_stat_gem_final(mrb_state *mrb)
{
}
