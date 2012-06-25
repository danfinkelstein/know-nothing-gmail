/*
 * LambdaProfiler
 *
 *   A userland performance counter-based counter profiler.  Allows
 * users with to configure performance counters and read them.  Also
 * provides a variety of userspace utilities to assist in
 * configuration, reading and accounting.
 *
 *    Copyright (C) 2010, John Demme, Columbia University
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <lprof.h>

//From lprof_asm.S -- Critical Sections
extern void __lp_sec0(void);
extern void __lp_sec1(void);
extern void __lp_sec2(void);
extern void __lp_sec3(void);
extern void __lp_sec_end(void);

struct lprof_stats __lp_stats;
static int num_ctrs;


// Register a crictical section with the kernel
static void registerCS(int i, void* b, void* e) {
    int rc;
    size_t cs_len = (uint64_t)e - (uint64_t)b;
    rc = sys_lprof_config(LPROF_DFN_CS, i, cs_len, 
			  (void*)b);
    if (rc < 0)
	perror("Error registering CS");
}

// Initialize counters
int lprof_init(unsigned int num, ...) {
    va_list args;
    int rc, ctr = 1;
    unsigned int conf;
    memset(&__lp_stats, 0, sizeof(struct lprof_stats));

    //Register critical sections for first 4 counters
    registerCS(0, __lp_sec0, __lp_sec1);
    registerCS(1, __lp_sec1, __lp_sec2);
    registerCS(2, __lp_sec2, __lp_sec3);
    registerCS(3, __lp_sec3, __lp_sec_end);

    //Configure each counter, staring with 1
    va_start(args, num);
    for (ctr=1; ctr<=num; ctr++) {
	conf = va_arg(args, unsigned int) & 0xFFFF;;
	printf("Configuring counter %d as %04x\n", ctr, conf);
	do {
	    rc = sys_lprof_config(LPROF_START, ctr, conf, &__lp_stats);
	} while (rc < 0 && errno == EBUSY);

	if (rc < 0) {
	    perror("Error configuring counter");
	}
    }
    va_end(args);

    num_ctrs = num;

    return rc;
}

//Close each counter
void lprof_close() {
    int i;
    for (i=0; i<=num_ctrs; i++)
	sys_lprof_config(LPROF_STOP, i, 0, 0);
}

