#ifndef _BLOOMFILTER_H
#define _BLOOMFILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../bitarr/bitarr.h"

#include "../hash/hash.h"

#define BLOOMFILTER_HASH_FUNCTION_COUNT     7   //This is "k"

typedef struct bloom_filter {
    hash_config_t hash_configs [BLOOMFILTER_HASH_FUNCTION_COUNT];   // Hash function configurations
    byte_t * bitarr;    // Underlying bit array
    unsigned num_bits;  // Size of the bit array in bits
} bloomfilt_t;

/**
 * Intializes a bloom filter
 * 
 * @param num_bits  the number of bits to initialize in the underlying bit array
 * @returns         a pointer to an empty bloom filter 
 */
inline bloomfilt_t * bloomfilter_init(unsigned num_bits);

/**
 * Inserts a key into a bloom filter
 * 
 * @param bloomfilt a pointer to the bloomfilter
 * @param key       a string to insert
 */
inline void bloomfilter_insert(bloomfilt_t * bloomfilt, char* key);

/**
 * Checks whether a key is in the bloom filter. 
 * 
 * False means the key is not in the bloom filter. True means the key may be in the bloom filter.
 * 
 * @param bloomfilt a pointer to the bloomfilter
 * @param key       a string to check
 * @returns A bool which is false only when the element definitly has not been inserted.
 */
inline bool bloomfilter_check(bloomfilt_t * bloomfilt, char* key);

#endif
