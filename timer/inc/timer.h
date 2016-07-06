#ifndef __TIMER__
#define __TIMER__

typedef void(*TIMER_FUNC)(int);

int create_timer(long first_sec, long first_usec, long inter_sec, long inter_usec, TIMER_FUNC);


#endif
