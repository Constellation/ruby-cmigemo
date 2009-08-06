#include "ruby.h"
#include "migemo.h"

struct RMigemo {
  int open;
  migemo *migemo;
};

static void rb_cmigemo_free(struct RMigemo*);
static VALUE rb_cmigemo_close(VALUE);
static VALUE rb_cmigemo_s_allocate(VALUE);
static VALUE rb_cmigemo_initialize(VALUE);
static VALUE rb_cmigemo_load(VALUE, VALUE, VALUE);
static VALUE rb_cmigemo_query(VALUE, VALUE);

static VALUE cCMigemo;

static VALUE
rb_cmigemo_s_allocate(VALUE klass)
{
  VALUE obj;
  struct RMigemo *rm;
  obj = Data_Make_Struct(klass, struct RMigemo, NULL, rb_cmigemo_free, rm);
  rm->open = 0;
  rm->migemo = NULL;
  return obj;
}

static void rb_cmigemo_free(struct RMigemo *rm)
{
  if(rm->open) migemo_close(rm->migemo);
  free(rm);
}

static VALUE
rb_cmigemo_initialize(VALUE self)
{
  char *dict;
  struct RMigemo *rm;
  int result;

  Data_Get_Struct(self, struct RMigemo, rm);
  rm->migemo = migemo_open(NULL);
  rm->open = 1;

  return self;
}

static VALUE
rb_cmigemo_close(VALUE self)
{
  struct RMigemo *rm;
  Data_Get_Struct(self, struct RMigemo, rm);
  if(rm->open){
    migemo_close(rm->migemo);
    rm->open = 0;
  }
  return Qnil;
}

static VALUE
rb_cmigemo_query(VALUE self, VALUE rstr)
{
  struct RMigemo *rm;
  unsigned char* str;
  migemo *m;
  VALUE result;

  Data_Get_Struct(self, struct RMigemo, rm);
  if(rm->open){
    str = migemo_query(rm->migemo, (unsigned char*)StringValuePtr(rstr));
    result = rb_tainted_str_new2(str);
    migemo_release(rm->migemo, str);
    return result;
  } else {
    rb_raise(rb_eException, "migemo closed");
  }
}

static VALUE
rb_cmigemo_load(VALUE self, VALUE id, VALUE rstr)
{
  struct RMigemo *rm;
  int result;
  int dict_id = NUM2INT(id);
  char *dict = StringValuePtr(rstr);
  Data_Get_Struct(self, struct RMigemo, rm);

  if(rm->open){
    result = migemo_load(rm->migemo, dict_id, dict);
    if(result == MIGEMO_DICTID_INVALID){
      rb_raise(rb_eArgError, "invalid dict file");
    }

    return INT2NUM(result);
  } else {
    rb_raise(rb_eException, "migemo closed");
  }
}

void Init_cmigemo()
{
  cCMigemo = rb_define_class("CMigemo", rb_cData);

  rb_define_alloc_func(cCMigemo, rb_cmigemo_s_allocate);
  rb_define_private_method(cCMigemo, "initialize", rb_cmigemo_initialize, 0);
  rb_define_method(cCMigemo, "query", rb_cmigemo_query, 1);
  rb_define_method(cCMigemo, "load", rb_cmigemo_load, 2);
  rb_define_method(cCMigemo, "close", rb_cmigemo_close, 0);

  rb_define_const(cCMigemo, "MIGEMO", INT2NUM(MIGEMO_DICTID_MIGEMO));
  rb_define_const(cCMigemo, "ROMA2HIRA", INT2NUM(MIGEMO_DICTID_ROMA2HIRA));
  rb_define_const(cCMigemo, "HIRA2KATA", INT2NUM(MIGEMO_DICTID_HIRA2KATA));
  rb_define_const(cCMigemo, "HAN2ZEN", INT2NUM(MIGEMO_DICTID_HAN2ZEN));
  rb_define_const(cCMigemo, "ZEN2HAN", INT2NUM(MIGEMO_DICTID_ZEN2HAN));
}

