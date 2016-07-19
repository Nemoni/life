#ifndef _LINK_LIST_
#define _LINK_LIST_
#include "a_star.h"

typedef struct LinkNode{
    struct LinkNode *next;
    SearchNode value;
}LinkNode;

unsigned int malloc_count_g;
unsigned int free_count_g;
    
int link_list_insert(LinkNode **head, SearchNode value);
int link_list_delete(LinkNode **head, SearchNode value);
int link_list_search(LinkNode *head, SearchNode **ppValue);
int link_list_destroy(LinkNode **head);
void print_link_list(LinkNode *head);
int link_list_resort(LinkNode **head);

#endif
