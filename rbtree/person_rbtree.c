#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbtree.h"
#include "person_rbtree.h"

rbtree_node *rbtree_search(struct rb_root *root, Type key)
{
    struct rb_node *rbnode = root->rb_node;
    
    while (rbnode!=NULL)
    {
        rbtree_node *node = container_of(rbnode, rbtree_node, rb_node);
 
        if (key < node->key)
            rbnode = rbnode->rb_left;
        else if (key > node->key)
            rbnode = rbnode->rb_right;
        else
            return node;
    }
      
    return NULL;    
}

int rbtree_insert(struct rb_root *root, rbtree_node node)
{
    rbtree_node *new_node = NULL;
    struct rb_node **tmp = &(root->rb_node), *parent = NULL;
    
    while (*tmp)
    {
        rbtree_node *p = container_of(*tmp, rbtree_node, rb_node);
        parent = *tmp;
        if (node.key < p->key)
            tmp = &((*tmp)->rb_left);
        else if (node.key > p->key)
            tmp = &((*tmp)->rb_right);
        else
            return -1;
    }
    
    if ((new_node = malloc(sizeof(rbtree_node))) == NULL)
        return -1; 
    memcpy(new_node, &node, sizeof(rbtree_node));
    
    /* Add new node and rebalance tree. */
    rb_link_node(&new_node->rb_node, parent, tmp);
    rb_insert_color(&new_node->rb_node, root);
    
    return 0;
}

void rbtree_delete(struct rb_root *root, Type key)
{
    rbtree_node *node;

    if ((node = rbtree_search(root, key)) == NULL)
        return ;

    rb_erase(&node->rb_node, root);
    free(node);
}

static void print_rbtree(struct rb_node *tree, Type key, int direction)
{
    if(tree != NULL)
    {   
        if(direction == 0)    // tree是根节点
            printf("%2d(B) is root\n", key);
        else                // tree是分支节点
            printf("%2d(%s) is %2d's %6s child\n", key, rb_is_black(tree)?"B":"R", key, direction==1?"right" : "left");

        if (tree->rb_left)
            print_rbtree(tree->rb_left, rb_entry(tree->rb_left, rbtree_node, rb_node)->key, -1);
        if (tree->rb_right)
            print_rbtree(tree->rb_right,rb_entry(tree->rb_right, rbtree_node, rb_node)->key,  1); 
    }   
}

void all_print(struct rb_root *root)
{
    if (root!=NULL && root->rb_node!=NULL)
        print_rbtree(root->rb_node, rb_entry(root->rb_node, rbtree_node, rb_node)->key,  0); 
    else
        printf("NULL\n");
}
/*
int main()
{
    struct rb_root mytree = RB_ROOT;
    rbtree_node node = {0};
                
    node.key = 2;
    node.c = 'b';
    rbtree_insert(&mytree, node);
   
    node.key = 3;
    node.c = 'c';
    rbtree_insert(&mytree, node);
    all_print(&mytree);

    rbtree_delete(&mytree, 2);
    all_print(&mytree);

    rbtree_delete(&mytree, 3);
    all_print(&mytree);
}*/
