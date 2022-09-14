#include "bitarr.h"

bitarr_t * bitarr_init(unsigned num_bits) {
    bitarr_t *b = (bitarr_t *) malloc(sizeof(bitarr_t));
    b->num_bits = num_bits;
    b->size = (num_bits+BITS_PER_BYTE-1)/BITS_PER_BYTE;

    //valloc manually allocates memory starting at a page boundary (https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_3.html)
    b->arr = (byte_t *) valloc(b->size);
}

void bitarr_free(bitarr_t * bitarr) {
    free(bitarr->arr);
    free(bitarr);
}

void bitarr_set(bitarr_t * bitarr, unsigned index) {
    unsigned section_index = index/BITS_PER_BYTE;
    unsigned bit_index = index % BITS_PER_BYTE;
    bitarr->arr[section_index] |= (1 << bit_index);
}

void bitarr_unset(bitarr_t * bitarr, unsigned index) {
    unsigned section_index = index/BITS_PER_BYTE;
    unsigned bit_index = index % BITS_PER_BYTE;
    bitarr->arr[section_index] &= ~(1 << bit_index);
}

bool bitarr_check(bitarr_t * bitarr, unsigned index) {
    unsigned section_index = index/BITS_PER_BYTE;
    unsigned bit_index = index % BITS_PER_BYTE;
    return (bool) bitarr->arr[section_index] & (1 >> bit_index);
}
