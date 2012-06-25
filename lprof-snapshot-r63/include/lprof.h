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

#ifndef _LPROF_H
#define _LPROF_H

#ifndef __LP_ASM_ONLY
#include <unistd.h>
#include <linux/lprof.h>

#define MAX_COUNTERS  64

// microarch neutral
#define EV_CYCLES	   (0x3C | (0x0 << 8))
#define EV_REF_CYCLES	   (0x3C | (0x1 << 8))
#define EV_INSTR	   (0xC0 | (0x0 << 8))
#define EV_BRANCH	   (0xC4 | (0x1 << 8))
#define EV_BRANCH_MISS     (0xC5 | (0x1 << 8))

// microarch specific
#define I7_L3_REFS	(0x2e | (0x4f << 8))
#define I7_L3_MISS	(0x2e | (0x41 << 8))

#define I7_L2_REFS	(0x24 | (0xff << 8))
#define I7_L2_MISS	(0x24 | (0xaa << 8))

#define I7_ICACHE_HITS  (0x80 | (0x01 << 8))
#define I7_ICACHE_MISS  (0x80 | (0x02 << 8))

#define I7_DL1_REFS     (0x43 | (0x01 << 8))

#define I7_LOADS        (0x0b | (0x01 << 8))
#define I7_STORES       (0x0b | (0x02 << 8))

#define I7_L2_DTLB_MISS (0x49 | (0x01 << 8))
#define I7_L2_ITLB_MISS (0x85 | (0x01 << 8))

#define I7_IO_TXNS      (0x6c | (0x01 << 8))
#define I7_DRAM_REFS    (0x0f | (0x20 << 8)

#ifdef __cplusplus
#include <string>
unsigned int get_event(std::string name);

 extern "C" {
#endif

extern struct lprof_stats __lp_stats;


int lprof_init(unsigned int num, ...);
void lprof_close();

#define RDX %%rdx
#define RAX %%rax

#endif

#define __QUOTEME_(...) #__VA_ARGS__
#define __QUOTEME(x) __QUOTEME_(x)
#define __LP_OFF(C) __lp_stats+24+(C)*8

#define __LP_ASM(C)				\
     rdpmc;					\
     shl $32, RDX;				\
     orq RAX, RDX;      			\
     subq __LP_OFF(C) , RDX;

// If this asm code is updated, update copy in lprof_asm.S
#define lprof(C, V)				\
     asm volatile (				\
	 __QUOTEME( __LP_ASM(C) )		\
     : "=d" (V)					\
     : "c" (C)					\
     : "%rax");

#define lprofd(C, V, CV)						\
     V = CV;								\
     lprof(C, CV)							\
     V = CV - V;

#ifdef __cplusplus
}
#endif

#endif //_LPROF_H
