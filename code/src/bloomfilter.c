#include "bloomfilter.h"

#define BF_INDEX(bloomfilt, key, config_index) ((unsigned int)(hash(key, bloomfilt->hash_configs[config_index]) % bloomfilt->num_bits))

bloomfilt_t * bloomfilter_init(unsigned num_bits, unsigned k) {
    bloomfilt_t *bf = (bloomfilt_t *) malloc(sizeof(bloomfilt_t));
    bloomfilter_init_at_addr(num_bits, k, bf);
    return bf;    
}

void bloomfilter_init_at_addr(unsigned num_bits, unsigned k, bloomfilt_t * bloomfilter_p) {
    unsigned j;
    
    bloomfilter_p->bitarr = INIT_BITARR(num_bits);
    bloomfilter_p->k = k;
    bloomfilter_p->num_bits = num_bits;

    for(j = 0; j < bloomfilter_p->k; j++) 
        bloomfilter_p->hash_configs[j] = generate_hash_config();
}

void bloomfilter_insert(bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    for(j=0; j < bloomfilt->k; j++) {
        SET_BITARR(bloomfilt->bitarr, BF_INDEX(bloomfilt, key, j));
    }
}

bool bloomfilter_check(bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    for(j=0; j < bloomfilt->k; j++) 
        if(!CHECK_BITARR(bloomfilt->bitarr, BF_INDEX(bloomfilt, key, j))) 
            return false;
    return true;
}
