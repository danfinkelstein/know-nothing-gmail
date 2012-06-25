/*
 * LambdaProfiler Fine-Grandularaity Userland Performance Counter support
 *
 *    Copyright (C) 2010, John Demme, Columbia University
 *
 */
#ifndef _LINUX_LPROF_H
#define _LINUX_LPROF_H

#ifndef __KERNEL__
#include <unistd.h>
#include <stdint.h>
#endif

#define MAX_PMCS   8
#define MAX_CS     8
#define MAX_CS_LEN 256

#define LPROF_OP_MASK   0x7

#define LPROF_STOP      (0)  //Start or stop profiling?
#define LPROF_START     (1)  //Start or stop profiling?
#define LPROF_DBG       (2)  //Print debug info to kernel log
#define LPROF_STATS     (3)  //Inform kernel about stats location
#define LPROF_DFN_CS    (4)  //Define instruction pattern of LP
			     //critical section
#define LPROF_DEL_CS    (5)  //Delete LP critical section

struct lprof_stats {
    unsigned char rdpmc_inprogress; /* Offset: 0 bytes */
    uint64_t context_switches;	    /* Offset: 8 byte */
    uint64_t timer_interrupts;	    /* Offset: 16 bytes */
    int64_t last[MAX_PMCS];	    /* Offsets: [0]: 24
				                [1]: 32 
						[2]: 40 ...*/
};

#ifndef __KERNEL__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define __NR_lprof_config 299

static inline int
sys_lprof_config(unsigned int op, unsigned int counter,
		 unsigned long long config, void* ptr)
{
    return syscall(__NR_lprof_config, op, counter, config, ptr);
}

#define DECLARE_ARGS(val, low, high)	unsigned low, high
#define EAX_EDX_VAL(val, low, high)	((low) | ((unsigned long long)(high) << 32))
#define EAX_EDX_ARGS(val, low, high)	"a" (low), "d" (high)
#define EAX_EDX_RET(val, low, high)	"=a" (low), "=d" (high)
static inline unsigned long long native_read_pmc(int counter)
{
	DECLARE_ARGS(val, low, high);

	asm volatile("rdpmc" : EAX_EDX_RET(val, low, high) : "c" (counter));
	return EAX_EDX_VAL(val, low, high);
}
#endif //__KERNEL__

#ifdef __KERNEL__

struct task_struct;
extern void exit_lprof(struct task_struct*);
extern void lprof_tick(void);
extern void lprof_switchto(struct task_struct *prev_p, struct task_struct *next_p);

#endif //__KERNEL__
#endif //_LINUX_LPROF_H
