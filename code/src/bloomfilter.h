#ifndef _BLOOMFILTER_H
#define _BLOOMFILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bitarr.h"

#include "hash.h"
#include "hash.djb2.c"

#define BITS_PER_ELEMENT    10
#define MAX_HASH_FUNCTIONS  20

typedef struct bloom_filter {
    unsigned k;                                         // Number of hash functions
    hash_config_t hash_configs [MAX_HASH_FUNCTIONS];    // Hash function configurations
    byte_t * bitarr;                                    // Underlying bit array
    unsigned num_bits;
} bloomfilt_t;

bloomfilt_t * bloomfilter_init(unsigned num_bits, unsigned k);

void bloomfilter_init_at_addr(unsigned num_bits, unsigned k, bloomfilt_t * addr);

void bloomfilter_insert(bloomfilt_t * bloomfilt, char* key);

bool bloomfilter_check(bloomfilt_t * bloomfilt, char* key);

#endif
