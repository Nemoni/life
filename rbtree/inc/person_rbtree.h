#ifndef __PERSON_RBTREE__
#define __PERSON_RBTREE__

typedef int Type;

typedef struct node{
    struct rb_node rb_node;
    Type key;
    unsigned int age;
}rbtree_node;

rbtree_node *rbtree_search(struct rb_root *root, Type key);
int rbtree_insert(struct rb_root *root, rbtree_node node);
void rbtree_delete(struct rb_root *root, Type key);
void all_print(struct rb_root *root);

#endif
