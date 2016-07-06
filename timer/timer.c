#include <stdio.h>    // for printf()
#include <signal.h>   // for signal()
#include <string.h>   // for memset()
#include <sys/time.h> // struct itimeral. setitimer()

#include "timer.h"

int create_timer(long first_sec, long first_usec, long inter_sec, long inter_usec, TIMER_FUNC timer_func)
{
    // Get system call result to determine successful or failed
    int res = 0;
    struct itimerval tick;

    // Register printMsg to SIGALRM
    signal(SIGALRM, timer_func);

    // Initialize struct
    memset(&tick, 0, sizeof(tick));

    // Timeout to run function first time
    tick.it_value.tv_sec = first_sec;  // sec
    tick.it_value.tv_usec = first_usec; // micro sec.

    // Interval time to run function
    tick.it_interval.tv_sec = inter_sec;
    tick.it_interval.tv_usec = inter_usec;

    // Set timer, ITIMER_REAL : real-time to decrease timer,
    //                          send SIGALRM when timeout
    res = setitimer(ITIMER_REAL, &tick, NULL);
    if (res) {
        printf("Set timer failed!!\n");
        return -1;
    }

    return 0;
}

