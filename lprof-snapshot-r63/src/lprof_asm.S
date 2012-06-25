# This code defines critical sections.  We use the macros from the
#   header file to make sure they match

#define  __LP_ASM_ONLY
#define RDX %rdx
#define RAX %rax
#include <lprof.h>

.text
	.global __lp_sec0
	.global __lp_sec1
	.global __lp_sec2
	.global __lp_sec3
	.global __lp_sec_end
	
__lp_sec0:
	__LP_ASM(0)
__lp_sec1:
	__LP_ASM(1)
__lp_sec2:
	__LP_ASM(2)
__lp_sec3:
	__LP_ASM(3)
__lp_sec_end:
	nop