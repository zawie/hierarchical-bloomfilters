#include "bloomfilter.h"

#define BF_INDEX(bloomfilt, key, config_index) ((unsigned int)(hash(key, bloomfilt->hash_configs[config_index]) % bloomfilt->num_bits))

inline void bloomfilter_insert(bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    for(j = 1; j <= BIT_SELECTORS; j++) {
        SET_BITARR(bloomfilt->bitarr, BF_INDEX(bloomfilt, key, j));
    }
}

inline bool bloomfilter_query(bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    for(j = 1; j <= BIT_SELECTORS; j++) 
        if(!CHECK_BITARR(bloomfilt->bitarr, BF_INDEX(bloomfilt, key, j))) 
            return false;
    return true;
}
