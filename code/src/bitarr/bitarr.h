#ifndef _BITARR_H
#define _BITARR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char byte_t;

#define BITS_PER_BYTE   8

#define GET_BYTE_INDEX(index)		(index/BITS_PER_BYTE)
#define GET_BIT_INDEX(index)		(index % BITS_PER_BYTE)

#define ROUND_BITS_TO_BYTES(bit_count)	((bit_count+BITS_PER_BYTE-1)/BITS_PER_BYTE)

/*
 * Bit arr operations as macros
 */
#define INIT_BITARR(num_bits)		((byte_t*) valloc(ROUND_BITS_TO_BYTES(num_bits)))
#define FREE_BITARR(bitarr_p)		(free((byte_t*) bitarr_p))
#define SET_BITARR(bitarr_p, index)	(((byte_t*) bitarr_p)[GET_BYTE_INDEX(index)] |= (1 << GET_BIT_INDEX(index)))
#define UNSET_BITARR(bitarr_p, index)	(((byte_t*) bitarr_p)[GET_BYTE_INDEX(index)] &= ~(1 << GET_BIT_INDEX(index)))
#define CHECK_BITARR(bitarr_p, index)	((bool) (((byte_t*) bitarr_p)[GET_BYTE_INDEX(index)] & (1 << GET_BIT_INDEX(index))))

#endif
