#ifndef __PERSON_RBTREE__
#define __PERSON_RBTREE__
#include "rbtree.h"

typedef int Type;

typedef struct node{
    struct rb_node rb_node;
    Type key;
    unsigned int age;
}rbtree_node;

extern rbtree_node *rbtree_search(struct rb_root *root, Type key);
extern int rbtree_insert(struct rb_root *root, rbtree_node node);
extern void rbtree_delete(struct rb_root *root, Type key);
extern void all_print(struct rb_root *root);

#endif
