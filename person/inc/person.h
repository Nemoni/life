#ifndef __person__
#define __person__

#include <pthread.h>

#define MAX_THREAD_NUM 3

typedef  void *(*THREAD_FUNC) (void *);

typedef struct{
    pthread_t id;
    pthread_attr_t *attr;
    THREAD_FUNC func;
    void *arg;
}THREAD_ARGS;

typedef struct {
    unsigned int person_id;
}TRANS_ARG;

void person();

#endif
