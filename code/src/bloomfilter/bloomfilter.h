#ifndef _BLOOMFILTER_H
#define _BLOOMFILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../bitarr/bitarr.h"

#include "../hash/hash.h"

#define BIT_SELECTORS       7   //This is "k"
#define HASH_CONFIGS        BIT_SELECTORS + 1   //Number of hash function configuration slots to save

typedef struct bloom_filter {
    hash_config_t hash_configs [HASH_CONFIGS];   // Hash function configurations
    byte_t * bitarr;    // Underlying bit array
    unsigned num_bits;  // Size of the bit array in bits
    unsigned num_pages; // Size of the bit array in bits
    unsigned sub_size;  // Size of sub filters in bits (hierarchical only)
} bloomfilt_t;

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
