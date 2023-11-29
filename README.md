# MD5 Library Overview

This is a slightly modified md5 implementation taken from https://people.csail.mit.edu/rivest/Md5.c.  The original code exists in original/Md5.c.  It has been modified to meet the needs of this library.  In particular, there are functions which convert a string to a 64 bit integer.

## md5.h - Header File

### Functions to convert a string or binary data to a 64-bit hash
* `uint64_t md5_hash(const void *d, size_t len)`: Computes a 64-bit hash for a given block of data.
* `uint64_t md5_hash_str(const char *s)`: Computes a 64-bit hash for a null-terminated string.

### Data Structure
- `md5_t`: The core data structure for MD5 computations. It contains:
    - `uint32_t i[2]`: Tracks the number of bits processed in the MD5 algorithm, mod 2^64.
    - `uint32_t buf[4]`: A scratch buffer holding data and transformations during computation.
    - `unsigned char in[64]`: An input buffer storing input blocks for processing.
    - `unsigned char digest[16]`: The final 128-bit MD5 hash result after the `md5_final` call.

### Original Functions
* `void md5_init(md5_t *m)`: Initializes an MD5 context for a new message digest computation.
* `void md5_update(md5_t *m, unsigned char *inBuf, unsigned int inLen)`: Processes input data in blocks, updating the MD5 context with new data.
* `void md5_final(md5_t *m)`: Finalizes the MD5 computation, producing the message digest (hash).

### Function to convert 128 digest to 64-bit.
* `uint64_t md5_take64(md5_t *m)`: Extracts a 64-bit hash value from the MD5 context, useful for applications requiring a shorter hash than the full 128-bit MD5 hash.



## Notes
- While MD5 is widely used, it's not recommended for cryptographic security due to vulnerabilities.
- This library focuses on ease of use and integration, making it suitable for general-purpose, non-security-critical applications.

For further details and updates, refer to the documentation and version history accompanying the library.