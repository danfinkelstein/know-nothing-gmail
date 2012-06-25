/* 
 * File:   lookup3.h
 * Author: Daniel Alex Finkelstein
 * $Id: hash.h 9 2010-08-19 17:42:20Z df2417 $
 *
 */

#ifndef LOOKUP3_H
#define	LOOKUP3_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>

/* only accepts uint32_t aligned arrays of uint32_t */
void hashword2(const uint32_t *key,  /* array of uint32_t */
	       size_t length,	     /* number of uint32_t values */
	       uint32_t *pc,	     /* in: seed1, out: hash1 */
	       uint32_t *pb);	     /* in: seed2, out: hash2 */

/* handles arbitrarily aligned arrays of bytes */
void hashlittle2(const void *key,   /* array of bytes */
		 size_t length,     /* number of bytes */
		 uint32_t *pc,      /* in: seed1, out: hash1 */
		 uint32_t *pb);     /* in: seed2, out: hash2 */

#ifdef	__cplusplus
}
#endif

#endif	/* LOOKUP3_H */

