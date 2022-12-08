#include "bloomfilter.h"

#define MAJOR_INDEX(bloomfilt, key)               ((unsigned int) HASH_MOD(key, bloomfilt->hash_configs[0], ((unsigned int) (bloomfilt->num_pages))))
#define MINOR_INDEX(bloomfilt, key, config_index) ((unsigned int) HASH_MOD(key, bloomfilt->hash_configs[config_index], bloomfilt->sub_size*8))
#define GET_SUBFILTER(bloomfilt, key)             ((byte_t *)     ( (byte_t *) bloomfilt->bitarr + MAJOR_INDEX(bloomfilt, key)*bloomfilt->sub_size))

inline void bloomfilter_insert(bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    byte_t * subfilter = GET_SUBFILTER(bloomfilt, key);
    for(j=1; j <= BIT_SELECTORS; j++) 
        SET_BITARR(subfilter, MINOR_INDEX(bloomfilt, key, j));
}

inline bool bloomfilter_query(bloomfilt_t * bloomfilt, char* key) {
    unsigned j;

    byte_t * subfilter = GET_SUBFILTER(bloomfilt, key);
    for(j=1; j <= BIT_SELECTORS; j++) 
        if(!CHECK_BITARR(subfilter, MINOR_INDEX(bloomfilt, key, j))) 
            return false;

    return true;
}
