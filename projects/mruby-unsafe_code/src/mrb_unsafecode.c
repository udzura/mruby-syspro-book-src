/*
** mrb_unsafecode.c - UnsafeCode class
**
** Copyright (c) Uchio Kondo 2020
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/error.h"
#include "mrb_unsafecode.h"
#include <stdio.h>
#include <string.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

static mrb_value mrb_unsafecode_check_password(mrb_state *mrb, mrb_value self)
{
  char test[32] = {0}, password[32] = {0};
  FILE *fh;
  char *got;
  mrb_int len;

  printf("test: %p, password: %p\n",
         test, password);

  mrb_get_args(mrb, "s", &got, &len);

  fh = fopen("/etc/app-password", "r");
  if(!fh)
    return mrb_nil_value();

  if(fread(password, sizeof(char), 31, fh) < -1)
    if(ferror(fh))
      mrb_sys_fail(mrb, "fread");
  fclose(fh);

  strncpy(test, got, (size_t)len);

  int i, j;
  for(i=0; i < 64; i += 32) {
        printf("%p: ", test+i);
    for(j=i; j < 32+i; ++j)
      if ((test+j)[0] == 0)
        printf("\\0");
      else
        printf("%c ", (test+j)[0]);
    printf("\n");
  }

  if(!strncmp(password, test, sizeof(password)))
    return mrb_true_value();
  else
    return mrb_false_value();
}

#include <mruby/array.h>
static mrb_value mrb_test_split_each(mrb_state *mrb, mrb_value self)
{
  mrb_value target, array;
  mrb_get_args(mrb, "S", &target);

  array = mrb_funcall(mrb, target, "split", 1, mrb_str_new_lit(mrb, ","));
  for(mrb_int i = 0; i < RARRAY_LEN(array); i++ ) {
    // ここで各文字列ごとの処理をする
    mrb_value current = mrb_ary_ref(mrb, array, i);
    mrb_p(mrb, current);
  }
  return array;
}

void mrb_mruby_unsafe_code_gem_init(mrb_state *mrb)
{
  struct RClass *unsafecode;
  unsafecode = mrb_define_class(mrb, "UnsafeCode", mrb->object_class);
  mrb_define_class_method(mrb, unsafecode, "check", mrb_unsafecode_check_password, MRB_ARGS_REQ(1));

  mrb_define_module_function(mrb, mrb->kernel_module, "runtest", mrb_test_split_each, MRB_ARGS_REQ(1));
  DONE;
}

void mrb_mruby_unsafe_code_gem_final(mrb_state *mrb)
{
}
