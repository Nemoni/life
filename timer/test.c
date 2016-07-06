#include <stdio.h>

#include "timer.h"

void timer_callback(int signo)
{
    printf("callback\n");
}

int main()
{
    create_timer(5, 0, 5, 0, timer_callback);

    while (1){

    }
}
