#ifndef RUBY_STREE_STRINGSET
#define RUBY_STREE_STRINGSET

#include <stree.h>

void Init_stree_stringset();
VALUE Stree_Wrap_StringSet(LST_StringSet * set);

#endif
