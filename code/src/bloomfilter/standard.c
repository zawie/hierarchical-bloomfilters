#include "standard.h"

#define BF_INDEX(bloomfilt, key, config_index) ((unsigned int)(hash(key, bloomfilt->hash_configs[config_index]) % bloomfilt->num_bits))

inline bloomfilt_t * bloomfilter_init(unsigned num_bits) {
    bloomfilt_t *bf = (bloomfilt_t *) malloc(sizeof(bloomfilt_t));
    unsigned j;
    
    bf->bitarr = INIT_BITARR(num_bits);
    bf->num_bits = num_bits;

    for(j = 0; j < BLOOMFILTER_HASH_FUNCTION_COUNT; j++) 
        bf->hash_configs[j] = generate_hash_config();    
    
    return bf;    
}

inline void bloomfilter_insert(bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    for(j=0; j < BLOOMFILTER_HASH_FUNCTION_COUNT; j++) {
        SET_BITARR(bloomfilt->bitarr, BF_INDEX(bloomfilt, key, j));
    }
}

inline bool bloomfilter_check(bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    for(j=0; j < BLOOMFILTER_HASH_FUNCTION_COUNT; j++) 
        if(!CHECK_BITARR(bloomfilt->bitarr, BF_INDEX(bloomfilt, key, j))) 
            return false;
    return true;
}
