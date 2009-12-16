#include <stree_string.h>

VALUE cStreeString;

static void dealloc(LST_String * ptr)
{
}

static VALUE allocate(VALUE klass)
{
  LST_String * ptr;
  return Data_Make_Struct(klass, LST_String, NULL, dealloc, ptr);
}

static VALUE initialize(VALUE self, VALUE string)
{
  LST_String * ptr;

  Data_Get_Struct(self, LST_String, ptr);
  lst_string_init(ptr, StringValuePtr(string), 1, RSTRING_LEN(string));

  return self;
}

static VALUE bytesize(VALUE self)
{
  LST_String * ptr;

  Data_Get_Struct(self, LST_String, ptr);
  return INT2NUM(lst_string_get_length(ptr));
}

void Init_stree_string()
{
  cStreeString = rb_define_class_under(cStree, "String", rb_cObject);
  rb_define_alloc_func(cStreeString, allocate);

  rb_define_method(cStreeString, "initialize", initialize, 1);
  rb_define_method(cStreeString, "bytesize", bytesize, 0);
}
