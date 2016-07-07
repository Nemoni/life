#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "person.h"
#include "person_rbtree.h"
#include "main.h"
#include "age.h"
#include "health.h"
#include "lifetime.h"

TRANS_ARG age_arg = {0};
TRANS_ARG lifetime_arg = {0};
TRANS_ARG health_arg = {0};

//extern THREAD_FUNC age_func;
//extern THREAD_FUNC lifetime_func;
//extern THREAD_FUNC health_func;

extern void *age_func(void *);
extern void *lifetime_func(void *);
extern void *health_func(void *);

extern unsigned int person_num_g;
extern struct rb_root life_tree;

THREAD_ARGS thread_info[MAX_THREAD_NUM] = {
	{0, NULL, &age_func, &age_arg},
	{0, NULL, &lifetime_func, &lifetime_arg},
	{0, NULL, &health_func, &health_arg}
};

int init_thread(unsigned int person_id)
{
	int i = 0;
	for (i=0; i<MAX_THREAD_NUM; i++){
		((TRANS_ARG *)thread_info[i].arg)->person_id = person_id;
		pthread_create(&thread_info[i].id, thread_info[i].attr, thread_info[i].func,  thread_info[i].arg);
	}
	
	return 0;
}

void person()
{
    rbtree_node node;
	memset(&node, 0, sizeof(rbtree_node));
                
	node.key = person_num_g;
	person_num_g++;
    rbtree_insert(&life_tree, node);
	
	init_thread(node.key);
	
	while (1){

	}

	return;    
}

