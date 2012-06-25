#ifndef _COMMON_H_
#define _COMMON_H_

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>

static inline void setcore(unsigned int c) {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(c, &mask);

    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0) {
	perror("Error setting cpu affinity");
    }

    sched_yield();
}

#endif //_COMMON_H_
