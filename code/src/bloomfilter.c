#include "bloomfilter.h"

#define BF_INDEX(bloomfilt, key, config_index) ((unsigned int)(hash(key, bloomfilt->hash_configs[config_index]) % bloomfilt->arr.num_bits))

bloomfilt_t * bloomfilter_init(int num_bits, int k) {
    bloomfilt_t *bf = (bloomfilt_t *) malloc(sizeof(bloomfilt_t));
    bloomfilter_init_at_addr(num_bits, k, bf);
    return bf;    
}

void bloomfilter_init_at_addr(int num_bits, int k, bloomfilt_t * addr) {
    int j;

    bitarr_init_at_addr(num_bits, &(addr->arr));
    addr->k = k;

    for(j = 0; j < addr->k; j++) 
        addr->hash_configs[j] = generate_hash_config();
}

void bloomfilter_insert(bloomfilt_t * bloomfilt, char* key) {
    int j;

    for(j=0; j < bloomfilt->k; j++) {
        bitarr_set(&(bloomfilt->arr), BF_INDEX(bloomfilt, key, j));
    }
}

bool bloomfilter_check(bloomfilt_t * bloomfilt, char* key) {
    int j;

    for(j=0; j < bloomfilt->k; j++) 
        if(!bitarr_check(&(bloomfilt->arr), BF_INDEX(bloomfilt, key, j))) 
            return false;
    return true;
}
