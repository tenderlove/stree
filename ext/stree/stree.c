#include <stree.h>

VALUE mSTree;

void Init_stree()
{
  mSTree = rb_define_module("STree");

  Init_stree_string();
}
