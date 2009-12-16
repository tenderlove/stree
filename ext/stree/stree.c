#include <stree.h>

VALUE cStree;

void Init_stree()
{
  cStree = rb_define_class("Stree", rb_cObject);
  Init_stree_string();
  Init_stree_stringset();
}
