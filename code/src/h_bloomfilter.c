#include "h_bloomfilter.h"

#define HASH(key, config, m)                    (hash(key, config) % m)

#define MAJOR_INDEX(bloomfilt, key)               ((unsigned int) HASH(key, bloomfilt->filter_hash_config, ((unsigned int) (bloomfilt->num_pages))))
#define MINOR_INDEX(bloomfilt, key, config_index) ((unsigned int) HASH(key, bloomfilt->hash_configs[config_index], PAGE_SIZE_BITS))
#define GET_SUBFILTER(bloomfilt, key)             ((byte_t *)     ( (byte_t *) bloomfilt->bitarr + MAJOR_INDEX(bloomfilt, key)*PAGE_SIZE_BYTES))

inline h_bloomfilt_t * h_bloomfilter_init(unsigned minimum_num_bits) {
    h_bloomfilt_t *bf = (h_bloomfilt_t *) malloc(sizeof(h_bloomfilt_t));
    unsigned j;
    
    unsigned num_bits = minimum_num_bits + (PAGE_SIZE_BITS - ((minimum_num_bits-1) % PAGE_SIZE_BITS)) + 1;

    assert(num_bits % PAGE_SIZE_BITS == 0);

    unsigned num_pages = num_bits/PAGE_SIZE_BITS;

    bf->bitarr = INIT_BITARR(num_bits);
    bf->num_bits = num_bits;
    bf->num_pages = num_pages;

    bf->filter_hash_config = generate_hash_config();
    for(j = 0; j < BIT_SELECTORS; j++) 
        bf->hash_configs[j] = generate_hash_config();    
    
    return bf;    
}

inline void h_bloomfilter_insert(h_bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    byte_t * subfilter = GET_SUBFILTER(bloomfilt, key);
    for(j=0; j < BIT_SELECTORS; j++) 
        SET_BITARR(subfilter, MINOR_INDEX(bloomfilt, key, j));
}

inline bool h_bloomfilter_check(h_bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    byte_t * subfilter = GET_SUBFILTER(bloomfilt, key);
    for(j=0; j < BIT_SELECTORS; j++) 
        if(!CHECK_BITARR(subfilter, MINOR_INDEX(bloomfilt, key, j))) 
            return false;
    return true;
}
