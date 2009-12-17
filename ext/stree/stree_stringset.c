#include <stree_stringset.h>

VALUE cStreeStringSet;

static void dealloc(void *ptr)
{
  LST_StringSet *set = (LST_StringSet *)ptr;
  lst_stringset_free(set);
}

static VALUE allocate(VALUE klass)
{
  LST_StringSet * ss = lst_stringset_new();
  return Data_Wrap_Struct(klass, NULL, dealloc, ss);
}

VALUE Stree_Wrap_StringSet(LST_StringSet * set)
{
  VALUE ss = Data_Wrap_Struct(cStreeStringSet, NULL, dealloc, set);
  rb_obj_call_init(ss, 0, NULL);
  return ss;
}

static VALUE push(VALUE self, VALUE string)
{
  LST_String * string_p = lst_string_new(
      StringValuePtr(string), sizeof(char), RSTRING_LEN(string));

  LST_StringSet * ss;

  Data_Get_Struct(self, LST_StringSet, ss);

  lst_stringset_add(ss, string_p);

  return self;
}

static VALUE length(VALUE self)
{
  LST_StringSet * ss;

  Data_Get_Struct(self, LST_StringSet, ss);
  return INT2NUM(ss->size);
}

static VALUE delete(VALUE self, VALUE string)
{
  LST_StringSet * ss;
  LST_String  * ss_string;

  Data_Get_Struct(self, LST_StringSet, ss);

  for(ss_string = ss->members.lh_first; ss_string; ss_string = ss_string->set.le_next)
  {
    VALUE tmp_string = rb_str_new2(lst_string_print(ss_string));
    if(Qtrue == rb_funcall(string, rb_intern("=="), 1, tmp_string)) {
      LIST_REMOVE(ss_string, set);
      ss->size--;
      return string;
    }
  }

  return Qnil;
}

static void each_cb(LST_String * string, void * ctx)
{
  rb_yield(rb_str_new2(lst_string_print(string)));
}

static VALUE each(VALUE self)
{
  LST_StringSet * ss;

  Data_Get_Struct(self, LST_StringSet, ss);
  lst_stringset_foreach(ss, each_cb, (void *)self);
  return self;
}

void Init_stree_stringset()
{
  cStreeStringSet = rb_define_class_under(cStree, "StringSet", rb_cObject);
  rb_define_alloc_func(cStreeStringSet, allocate);

  rb_define_method(cStreeStringSet, "push", push, 1);
  rb_define_method(cStreeStringSet, "length", length, 0);
  rb_define_method(cStreeStringSet, "delete", delete, 1);
  rb_define_method(cStreeStringSet, "each", each, 0);
}
