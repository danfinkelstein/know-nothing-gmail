#define _BSD_SOURCE
#define _GNU_SOURCE

#include <lprof.h>
#include <linux/lprof.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <sched.h>

struct lprof_stats stats;

double d = 9.0;
void foo(void) {
    size_t i;
    for (i=0; i<100000000; i++) {
	d *= d + 8 / (d * d) + (d/8);
    }
}

int main(void) {
    int ctr, rc;
    size_t i;
    pcount_t c;
    cpu_set_t mask;
    struct sched_param sp;
    memset(&sp, 0, sizeof(sp));
    CPU_ZERO(&mask);
    CPU_SET(8, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

    sp.sched_priority = 20;
    rc = sched_setscheduler(0, SCHED_FIFO, &sp);
    if (rc != 0) {
    	perror("setting RT priority");
    	//return rc;
    }

    memset(&stats, 0, sizeof(struct lprof_stats));

    /* ctr = lprof_config(EV_REF_CYCLES); */
    /* lprof_stat(&stats); */
    /* //ctr = lprof_config(EV_INSTR); */
    /* lprofd(); */
    for (i=0; i<50; i++) {
         foo();
    }
    /* c = lprofd(); */
    /* printf("Cycles, %llu, Timer Ints, %lu, Context Sw, %lu\n", */
    /* 	   c, stats.timer_interrupts, stats.context_switches); */
    /* lprof_close(ctr); */
    return 0;
}
