#ifndef _H_BLOOMFILTER_H
#define _H_BLOOMFILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>

#include "bitarr.h"

#include "hash/hash.h"

#define BIT_SELECTORS       7   //This is "k"
//Note: this implementation only works when there is one bloom filter selector; e.g l = 1

#define PAGE_SIZE_BYTES         ((unsigned) 4096)                //Page size in bytes
#define PAGE_SIZE_BITS          ((unsigned) (8*PAGE_SIZE_BYTES)) //Page size in bits

typedef struct h_bloom_filter {
    hash_config_t filter_hash_config;             // Hash function configuration to select bloom filter.
    hash_config_t hash_configs [BIT_SELECTORS];   // Hash function configurations to select bits
    byte_t * bitarr;    // Underlying bit array
    unsigned num_bits;  // Size of the bit array in bits
    unsigned num_pages;  // Size of the bit array in bits
} h_bloomfilt_t;

/**
 * Intializes a bloom filter.
 * 
 * Note, the underlying bit array will contain a number of bytes which is a multiple of PAGE_SIZE
 * 
 * @param minimum_num_bits  the minimum number of bits to initialize in the underlying bit array
 * @returns                 a pointer to an empty bloom filter 
 */
h_bloomfilt_t * h_bloomfilter_init(unsigned minimum_num_bits);

/**
 * Inserts a key into a bloom filter
 * 
 * @param bloomfilt a pointer to the bloomfilter
 * @param key       a string to insert
 */
void h_bloomfilter_insert(h_bloomfilt_t * bloomfilt, char* key);

/**
 * Checks whether a key is in the bloom filter. 
 * 
 * False means the key is not in the bloom filter. True means the key may be in the bloom filter.
 * 
 * @param bloomfilt a pointer to the bloomfilter
 * @param key       a string to check
 * @returns A bool which is false only when the element definitly has not been inserted.
 */
bool h_bloomfilter_check(h_bloomfilt_t * bloomfilt, char* key);

#endif
