#ifndef _LP_COMMON_H_
#define _LP_COMMON_H_

#include <stdint.h>

#ifndef MAX_CS
#define MAX_CS 8
#endif

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct {
    uint64_t ip;		/* Offset: 0 */
    union {
	const char* name;
	uint64_t nameAddr;	/* Offset: 8 */
    };
    uint64_t p;			/* Offset: 16 */
    uint64_t callCount;		/* Offset: 24 */
    uint64_t inc;		/* Offset: 32 */
    uint64_t interrupts; 	/* Offset: 40 */
    uint64_t context_switches;	/* Offset: 48 */
} Result;

typedef struct {
    uint32_t version;
    uint32_t counters;
    void*    cs_marker_pairs[2*MAX_CS];
} InstrumentationInfo;

#ifdef __cplusplus
}
#endif

#endif
