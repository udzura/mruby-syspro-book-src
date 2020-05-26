/*
** mrb_firstgem.c - FirstGem class
**
** Copyright (c) Uchio Kondo 2020
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_firstgem.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  mrb_int len;
} mrb_firstgem_data;

static const struct mrb_data_type mrb_firstgem_data_type = {
  "mrb_firstgem_data", mrb_free,
};

static mrb_value mrb_firstgem_init(mrb_state *mrb, mrb_value self)
{
  mrb_firstgem_data *data;
  char *str;
  mrb_int len;

  data = (mrb_firstgem_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_firstgem_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_firstgem_data *)mrb_malloc(mrb, sizeof(mrb_firstgem_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_firstgem_hello(mrb_state *mrb, mrb_value self)
{
  mrb_firstgem_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_firstgem_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_first_gem_gem_init(mrb_state *mrb)
{
  struct RClass *firstgem;
  firstgem = mrb_define_class(mrb, "FirstGem", mrb->object_class);
  mrb_define_method(mrb, firstgem, "initialize", mrb_firstgem_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, firstgem, "hello", mrb_firstgem_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, firstgem, "hi", mrb_firstgem_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_first_gem_gem_final(mrb_state *mrb)
{
}

