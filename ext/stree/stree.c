#include <stree.h>

VALUE cStree;

static void dealloc(void *ptr)
{
  // FIXME: Strings don't seem to be duped when adding to the tree, so we
  // need to figure out a tree free strategy.  We'll just leak for now.
  //lst_stree_free((LST_STree *)ptr);
}

static VALUE allocate(VALUE klass)
{
  LST_STree * ptr;
  VALUE rb = Data_Make_Struct(klass, LST_STree, NULL, dealloc, ptr);
  lst_stree_init(ptr);
  return rb;
}

static VALUE push(VALUE self, VALUE o)
{
  LST_STree * tree;
  LST_String * string;

  if(cStreeString != rb_obj_class(o))
    rb_raise(rb_eArgError, "must be of type Stree::String");

  Data_Get_Struct(self, LST_STree, tree);
  Data_Get_Struct(o, LST_String, string);

  lst_stree_add_string(tree, string);

  return self;
}

static VALUE longest_common_substr(VALUE self, VALUE min_len, VALUE max_len)
{
  LST_STree * ptr;

  Data_Get_Struct(self, LST_STree, ptr);

  LST_StringSet * set =
    lst_alg_longest_common_substring(ptr, NUM2INT(min_len), NUM2INT(max_len));

  return Stree_Wrap_StringSet(set);
}

void Init_stree()
{
  cStree = rb_define_class("Stree", rb_cObject);

  rb_define_alloc_func(cStree, allocate);
  rb_define_method(cStree, "push", push, 1);
  rb_define_method(cStree, "longest_common_substr", longest_common_substr, 2);

  Init_stree_string();
  Init_stree_stringset();
}
