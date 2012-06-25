#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sched.h>
#include <linux/lprof.h>
#include <lprof.h>
#include <math.h>
#include <pthread.h>

#define NUM_THREADS 4

__thread struct lprof_stats stats;

extern void test();
extern void lp_end();
extern void lp();

static __thread double d = 9.0;
void burn(void) {
    uint64_t i;
    for (i=0; i<8000000; i++) {
	d *= d;
	d = sqrt(d);
    }
}

void* threadGo(void* tidv) {
    size_t rc, tid = (size_t)tidv;
    uint64_t i;

    unsigned long conf;

    printf("Stats addr: %p\n", &stats);
    conf = 0xC0; //Instructions Retired
    rc = sys_lprof_config(LPROF_START, 1, conf, &stats);
    if (rc < 0) {
    	perror("opening counter");
    	exit(-1);
    }

    conf = 0x3C; //UnHalted Core Cycle

    rc = sys_lprof_config(LPROF_START, 2, conf, &stats);
    if (rc < 0) {
    	perror("opening counter");
    	exit(-1);
    }

    for (i=0; i<10; i++) {
	burn();
    }

    int64_t ctr1 = lprof_ctr(1);
    ctr1 -= stats.last[1];
    int64_t ctr2 = lprof_ctr(2);
    ctr2 -= stats.last[2];

    //Shut it down
    rc = sys_lprof_config(LPROF_STOP, 1, 0, 0);
    if (rc < 0) {
    	perror("closing counter");
    	exit(-1);
    }

    //Shut it down
    rc = sys_lprof_config(LPROF_STOP, 2, 0, 0);
    if (rc < 0) {
    	perror("closing counter");
    	exit(-1);
    }

    printf("T%lu rdmpc1:   %10ld\n", tid, ctr1);
    printf("T%lu rdmpc1: 0x%llx\n", tid, (unsigned long long)ctr1);

    printf("T%lu rdmpc2:   %10ld\n", tid, ctr2);
    printf("T%lu rdmpc2: 0x%llx\n", tid, (unsigned long long)ctr2);

    return NULL;
}

int main() { 
    int i;
    pthread_t threads[NUM_THREADS];
    
    memset(&stats, 0, sizeof(struct lprof_stats));

        for (i=0; i<NUM_THREADS; i++) {
	pthread_create(&threads[i], NULL, threadGo, (void*)(uint64_t)i);
    }

    for (i=0; i<5; i++) 
	burn();

    for (i=0; i<NUM_THREADS; i++) {
	pthread_join(threads[i], NULL);
    }

    return 0;
}
