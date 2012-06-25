#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sched.h>
#include <linux/lprof.h>

#define ARCH_PERFMON_EVENTSEL_ENABLE			  (1 << 22)
#define ARCH_PERFMON_EVENTSEL_INT			  (1 << 20)
#define ARCH_PERFMON_EVENTSEL_OS			  (1 << 17)
#define ARCH_PERFMON_EVENTSEL_USR			  (1 << 16)

static inline unsigned long long ctr(void) {
    static unsigned long long last = 0;
    unsigned long long delta, ret;
    ret = native_read_pmc(1);
    delta = ret - last;
    last = ret;
    return delta;
}

#define N_ITER 50
static unsigned long long ticks[N_ITER];
static void appCtr(void) {
    static size_t i = 0;
    ticks[i++] = ctr();
}

double d = 9.0;
void bar(void) {
    int i;
    for (i=0; i<40000000; i++) {
	d = d * d;
	d += 8.5;
    }
}

void foo(void) {
    unsigned long i;
    for (i=0; i<N_ITER; i++) {
	bar();
	appCtr();
	sched_yield();
   }
}

static void info(void) {
    size_t i;
    for (i=0; i<N_ITER; i++) {
	printf("%llu\n", ticks[i]);
    }
}

int main() { 
    int rc;
    unsigned long conf;

    conf = ARCH_PERFMON_EVENTSEL_ENABLE
	|  ARCH_PERFMON_EVENTSEL_USR
        | 0xC0; //Instructions Retired
    //|  0x3C; //UnHalted Core Cycles


    rc = sys_lprof_config(LPROF_START, 1, conf, 0);
    if (rc < 0) {
	perror("opening counter");
	exit(-1);
    }

    foo();

    //Shut it down
    rc = sys_lprof_config(0, 1, conf, 0);
    if (rc < 0) {
	perror("closing counter");
	exit(-1);
    }

    info();

    return 0;
}
