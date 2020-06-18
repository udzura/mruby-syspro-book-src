/*
** mrb_firstc.c - FirstC class
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
#include <mruby/error.h>
#include <mruby/string.h>
#include "mrb_firstc.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

static mrb_value mrb_my_uname(mrb_state *mrb, mrb_value self) {
  struct utsname uts;
  mrb_value ret;
  if (uname(&uts) == -1) {
    mrb_sys_fail(mrb, "uname failed");
  }

  ret = mrb_str_new_cstr(mrb, uts.nodename);
  return ret;
}

static mrb_value mrb_my_stat_size(mrb_state *mrb, mrb_value self) {
  struct stat buf;
  char *pathname;
  mrb_get_args(mrb, "z", &pathname);
  int ret = stat(pathname, &buf);
  if (ret == -1) {
    mrb_sys_fail(mrb, "stat failed");
  }

  return mrb_fixnum_value((mrb_int)buf.st_size);
}

void mrb_mruby_first_c_gem_init(mrb_state *mrb)
{
  struct RClass *firstc;
  firstc = mrb_define_class(mrb, "FirstC", mrb->object_class);
  mrb_define_class_method(mrb, firstc, "my_uname", mrb_my_uname, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, firstc, "my_stat_size", mrb_my_stat_size, MRB_ARGS_REQ(1));
  DONE;
}

void mrb_mruby_first_c_gem_final(mrb_state *mrb)
{
}
