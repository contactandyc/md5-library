/* the code below is taken from https://people.csail.mit.edu/rivest/Md5.c */

/*
 **********************************************************************
 ** md5.h -- Header file for implementation of MD5                   **
 ** RSA Data Security, Inc. MD5 Message Digest Algorithm             **
 ** Created: 2/17/90 RLR                                             **
 ** Revised: 12/27/90 SRD,AJ,BSK,JT Reference C version              **
 ** Revised (for MD5): RLR 4/27/91                                   **
 **   -- G modified to have y&~z instead of y&z                      **
 **   -- FF, GG, HH modified to add in last register done            **
 **   -- Access pattern: round 2 works mod 5, round 3 works mod 3    **
 **   -- distinct additive constant for each step                    **
 **   -- round 4 added, working mod 7                                **
 **********************************************************************
 */

/*
 **********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved. **
 **                                                                  **
 ** License to copy and use this software is granted provided that   **
 ** it is identified as the "RSA Data Security, Inc. MD5 Message     **
 ** Digest Algorithm" in all material mentioning or referencing this **
 ** software or this function.                                       **
 **                                                                  **
 ** License is also granted to make and use derivative works         **
 ** provided that such works are identified as "derived from the RSA **
 ** Data Security, Inc. MD5 Message Digest Algorithm" in all         **
 ** material mentioning or referencing the derived work.             **
 **                                                                  **
 ** RSA Data Security, Inc. makes no representations concerning      **
 ** either the merchantability of this software or the suitability   **
 ** of this software for any particular purpose.  It is provided "as **
 ** is" without express or implied warranty of any kind.             **
 **                                                                  **
 ** These notices must be retained in any copies of any part of this **
 ** documentation and/or software.                                   **
 **********************************************************************
 */

#ifndef _md5_H
#define _md5_H

#include <inttypes.h>
#include <stddef.h>

/* Data structure for MD5 (Message Digest) computation */
typedef struct {
  uint32_t i[2];       /* Number of _bits_ handled mod 2^64. This array keeps track of
                          the number of bits processed in the MD5 algorithm. */
  uint32_t buf[4];     /* Scratch buffer. This array temporarily holds data and transformations
                          in the MD5 computation process. */
  unsigned char in[64];/* Input buffer. This array stores the input blocks to be processed
                          by the MD5 algorithm. */
  unsigned char digest[16]; /* Actual digest after MD5Final call. This array stores the
                               128-bit MD5 hash result. */
} md5_t;

/* Initializes an MD5 context for a new message digest computation. */
void md5_init(md5_t *m);

/* Processes input data in blocks, updating the MD5 context with the new data. */
void md5_update(md5_t *m, unsigned char *inBuf, unsigned int inLen);

/* Finalizes the MD5 computation and produces the message digest (hash). */
void md5_final(md5_t *m);

/* Extracts a 64-bit hash value from the MD5 context. Useful for applications
   that require a shorter hash than the standard 128-bit MD5 hash. */
uint64_t md5_take64(md5_t *m);

/* Computes a 64-bit hash value from the MD5 context for a given block of data. */
uint64_t md5_hash(const void *d, size_t len);

/* Computes a 64-bit hash value from the MD5 context for a null-terminated string. */
uint64_t md5_hash_str(const char *s);

#endif
