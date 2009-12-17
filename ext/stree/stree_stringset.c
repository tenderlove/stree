#include <stree_stringset.h>

VALUE cStreeStringSet;

static void dealloc(void *ptr)
{
  LST_StringSet *set = (LST_StringSet *)ptr;

  free(set);
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

static VALUE push(VALUE self, VALUE sstring)
{
  if(cStreeString != rb_obj_class(sstring))
    rb_raise(rb_eArgError, "must be of type Stree::String");

  VALUE weakrefs = rb_iv_get(self, "@weak_refs");

  LST_String * sstring_p;
  LST_StringSet * ss;

  Data_Get_Struct(sstring, LST_String, sstring_p);
  Data_Get_Struct(self, LST_StringSet, ss);

  VALUE key = INT2NUM((int)sstring_p);
  rb_hash_aset(weakrefs, key, sstring);

  lst_stringset_add(ss, sstring_p);

  return self;
}

static VALUE length(VALUE self)
{
  LST_StringSet * ss;

  Data_Get_Struct(self, LST_StringSet, ss);
  return INT2NUM(ss->size);
}

static VALUE delete(VALUE self, VALUE obj)
{
  if(cStreeString != rb_obj_class(obj))
    rb_raise(rb_eArgError, "must be of type Stree::String");

  LST_String * sstring_p;
  LST_StringSet * ss;

  Data_Get_Struct(obj, LST_String, sstring_p);
  Data_Get_Struct(self, LST_StringSet, ss);

  int before = ss->size;
  lst_stringset_remove(ss, sstring_p);

  if(ss->size != before) return obj;
  return Qnil;
}

static void each_cb(LST_String * string, void * ctx)
{
  VALUE self = (VALUE)ctx;

  VALUE weakrefs = rb_iv_get(self, "@weak_refs");
  VALUE key = INT2NUM((int)string);
  VALUE value = rb_hash_aref(weakrefs, key);

  // If this wasn't in a weak ref table, we'll assume that some other Ruby
  // object created it and is in charge of freeing it's memory.
  if(NIL_P(value))
    value = Data_Wrap_Struct(cStreeString, NULL, NULL, string);

  rb_yield(value);
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
