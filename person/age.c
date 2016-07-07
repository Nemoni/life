#include <stdio.h>

#include "timer.h"
#include "rbtree.h"
#include "person_rbtree.h"
#include "person.h"
#include "main.h"

rbtree_node *age_node_p = NULL;

extern struct rb_root life_tree;

void age_grow(int signo)
{
	age_node_p->age++;
printf("age_grow age_node_p->age:%d\n", age_node_p->age);
}

void *age_func(void *arg)
{	
	TRANS_ARG *age_arg = (TRANS_ARG *)arg;
printf("age thread arg person_id:%d\n", age_arg->person_id);
	age_node_p = rbtree_search(&life_tree, age_arg->person_id);
	create_timer(5,0,5,0,age_grow);

	while (1){

	}
}
