#include <stree_string.h>

VALUE cStreeString;

static void dealloc(void * ptr)
{
  lst_string_free((LST_String *)ptr);
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
  lst_string_init(ptr, StringValuePtr(string), sizeof(char), RSTRING_LEN(string));

  return self;
}

static VALUE bytesize(VALUE self)
{
  LST_String * ptr;

  Data_Get_Struct(self, LST_String, ptr);
  return INT2NUM(lst_string_get_length(ptr));
}

static VALUE get(VALUE self, VALUE index)
{
  LST_String * ptr;

  Data_Get_Struct(self, LST_String, ptr);

  void * item = lst_string_get_item(ptr, NUM2INT(index));

  if(NULL == item) return Qnil;

  char * c = ((char *)item)[0];

  if(c) return INT2NUM(((char *)item)[0]);
  return Qnil;
}

static VALUE to_s(VALUE self)
{
  LST_String * ptr;

  Data_Get_Struct(self, LST_String, ptr);
  return rb_str_new2(lst_string_print(ptr));
}

void Init_stree_string()
{
  cStreeString = rb_define_class_under(cStree, "String", rb_cObject);
  rb_define_alloc_func(cStreeString, allocate);

  rb_define_method(cStreeString, "initialize", initialize, 1);
  rb_define_method(cStreeString, "bytesize", bytesize, 0);
  rb_define_method(cStreeString, "[]", get, 1);
  rb_define_method(cStreeString, "to_s", to_s, 0);
}
