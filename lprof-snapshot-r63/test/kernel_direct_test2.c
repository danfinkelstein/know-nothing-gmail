#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sched.h>
#include <linux/lprof.h>
#include <lprof.h>

#define ARCH_PERFMON_EVENTSEL_ENABLE			  (1 << 22)
#define ARCH_PERFMON_EVENTSEL_INT			  (1 << 20)
#define ARCH_PERFMON_EVENTSEL_OS			  (1 << 17)
#define ARCH_PERFMON_EVENTSEL_USR			  (1 << 16)

struct lprof_stats stats;

extern void test();
extern void lp_end();
extern void lp();

uint64_t hits = 0;

void hitClear(int64_t i) {
    hits++;
    int64_t ctr1 = lprof_ctr(1);
    int64_t cctr1 = ctr1 - stats.last[1];
    printf("Hit clear on %10ld, 0x%12lx, %12ld, 0x%12lxx\n", i, ctr1, cctr1, -1*stats.last[1]);
}

int main() { 
    int rc, i;
    unsigned long conf;
    uint64_t cs_len;

    memset(&stats, 0, sizeof(struct lprof_stats));

    conf = ARCH_PERFMON_EVENTSEL_ENABLE
	|  ARCH_PERFMON_EVENTSEL_USR
        | 0xC0; //Instructions Retired
	//|  0x3C; //UnHalted Core Cycles


    rc = sys_lprof_config(LPROF_START, 1, conf, &stats);
    if (rc < 0) {
    	perror("opening counter");
    	exit(-1);
    }

    conf = ARCH_PERFMON_EVENTSEL_ENABLE
	|  ARCH_PERFMON_EVENTSEL_USR
	|  0x3C; //UnHalted Core Cycle

    rc = sys_lprof_config(LPROF_START, 2, conf, &stats);
    if (rc < 0) {
    	perror("opening counter");
    	exit(-1);
    }

    cs_len = ((uint64_t)lp_end) - ((uint64_t)lp);
    printf("Defining CS: %p, %lu\n", lp, cs_len);
    rc = sys_lprof_config(LPROF_DFN_CS, 0, cs_len, lp);
    if (rc < 0) {
    	perror("defining critical section");
    	exit(rc);
    }

    for (i=0; i<10; i++) {
	test();
    }

    int64_t ctr1 = lprof_ctr(1);
    ctr1 -= stats.last[1];
    int64_t ctr2 = lprof_ctr(2);
    ctr2 -= stats.last[2];

    //Shut it down
    rc = sys_lprof_config(LPROF_STOP, 1, conf, 0);
    if (rc < 0) {
    	perror("closing counter");
    	exit(-1);
    }

    //Shut it down
    rc = sys_lprof_config(LPROF_STOP, 2, conf, 0);
    if (rc < 0) {
    	perror("closing counter");
    	exit(-1);
    }

    printf("rdmpc1:   %10ld\n", ctr1);
    printf("rdmpc1: 0x%llx\n", (unsigned long long)ctr1);

    printf("rdmpc2:   %10ld\n", ctr2);
    printf("rdmpc2: 0x%llx\n", (unsigned long long)ctr2);

    printf("Context Switches: %lu\nInterrupts: %lu\nHits: %lu\n",
	   stats.context_switches, stats.timer_interrupts, hits);

    return 0;
}
