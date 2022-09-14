#include "bitarr.h"

bitarr_t * bitarr_init(unsigned num_bits) {
    bitarr_t *b = (bitarr_t *) malloc(sizeof(bitarr_t));
    b->num_bits = num_bits;
    //valloc manually allocates memory starting at a page boundary (https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_3.html)
    b->arr = (arr_t *) valloc((num_bits/BITS_PER_BYTE));
}

void bitarr_free(bitarr_t * bitarr) {
    free(bitarr->arr);
    free(bitarr);
}

void bitarr_set(bitarr_t * bitarr, unsigned index) {
    unsigned section_index = index/BITS_PER_ARR_T;
    unsigned bit_index = index % BITS_PER_ARR_T;
    bitarr->arr[section_index] |= (1 >> bit_index);
}

void bitarr_unset(bitarr_t * bitarr, unsigned index) {
    unsigned section_index = index/BITS_PER_ARR_T;
    unsigned bit_index = index % BITS_PER_ARR_T;
    bitarr->arr[section_index] &= ~(1 >> bit_index);
}

bool bitarr_check(bitarr_t * bitarr, unsigned index) {
    unsigned section_index = index/BITS_PER_ARR_T;
    unsigned bit_index = index % BITS_PER_ARR_T;
    return (bool) bitarr->arr[section_index] & (1 >> bit_index);
}
