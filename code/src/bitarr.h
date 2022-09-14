#ifndef _BITARR_H
#define _BITARR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define byte_t          char
#define BITS_PER_BYTE   8

#define IS_VALID_INDEX (bitarr, index) ((bool) (((unsigned) index) < bitarr->num_bits)) //Used to check if an index is valid

typedef struct bit_arry {
    size_t num_bits;
    size_t size;
    byte_t* arr;
} bitarr_t;

/**
 * Intializes a bit array of a specified size starting at a page boundary.
 * 
 * @param num_bits the number of bits desired in the bit array
 * @return a struct pointer representing the data structure
 */
bitarr_t * bitarr_init(unsigned num_bits);

/**
 * Frees all memory allocated to create the bit array
 * 
 * @param bitarr the bit array to free
 */
void bitarr_free(bitarr_t * bitarr);

/**
 * Sets the bit at the specified index.
 * 
 * @param bitarr the bit array to set
 * @param index the bit to set
 */
void bitarr_set(bitarr_t * bitarr, unsigned index);

/**
 * Unsets the bit at the specified index.
 * 
 * @param bitarr the bit array to modify
 * @param index the bit to unset
 */
void bitarr_unset(bitarr_t * bitarr, unsigned index);


/**
 * Checks whether the bit at the specified index is set.
 * 
 * @param bitarr the bit array to modify
 * @param index the bit to check
 */
bool bitarr_check(bitarr_t * bitarr, unsigned index);

#endif