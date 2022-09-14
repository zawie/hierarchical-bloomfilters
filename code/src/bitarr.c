#include "bitarr.h"

#define GET_BYTE_INDEX(index) (index/BITS_PER_BYTE)
#define GET_BIT_INDEX(index) (index % BITS_PER_BYTE)

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
    bitarr->arr[GET_BYTE_INDEX(index)] |= (1 << GET_BIT_INDEX(index));
}

void bitarr_unset(bitarr_t * bitarr, unsigned index) {
    bitarr->arr[GET_BYTE_INDEX(index)] &= ~(1 << GET_BIT_INDEX(index));
}

bool bitarr_check(bitarr_t * bitarr, unsigned index) {
    return (bool) (bitarr->arr[GET_BYTE_INDEX(index)] & (1 << GET_BIT_INDEX(index)));
}
