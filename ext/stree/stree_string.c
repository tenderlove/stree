#include <stree_string.h>

static void deallocate(void * string)
{
  lst_string_free((LST_String *)string);
}

static VALUE allocate(VALUE klass)
{
  LST_String * string = malloc(sizeof(LST_String));

  return Data_Wrap_Struct(klass, NULL, deallocate, string);
}

static VALUE initialize(VALUE self, VALUE rb_string)
{
  LST_String * string;
  void * data;

  Check_Type(rb_string, T_STRING);

  Data_Get_Struct(self, LST_String, string);

  data = calloc(RSTRING_LEN(rb_string), sizeof(char));
  memcpy(data, StringValuePtr(rb_string), RSTRING_LEN(rb_string));

  lst_string_init(
      string,
      data,
      sizeof(char),
      RSTRING_LEN(rb_string));

  return self;
}

static VALUE length(VALUE self)
{
  LST_String * string;

  Data_Get_Struct(self, LST_String, string);

  return INT2NUM(lst_string_get_length(string));
}

void Init_stree_string()
{
  VALUE cSTreeString = rb_define_class_under(mSTree, "String", rb_cObject);

  rb_define_alloc_func(cSTreeString, allocate);
  rb_define_method(cSTreeString, "initialize", initialize, 1);
  rb_define_method(cSTreeString, "length", length, 0);
}
