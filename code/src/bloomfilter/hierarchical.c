#include "bloomfilter.h"

#define PAGE_SIZE_BYTES         ((unsigned) 4096)  //Page size in bytes
#define PAGE_SIZE_BITS          ((unsigned) 32768) //Page size in bits

#define HASH(key, config, m)                    (hash(key, config) % m)

#define MAJOR_INDEX(bloomfilt, key)               ((unsigned int) HASH(key, bloomfilt->hash_configs[0], ((unsigned int) (bloomfilt->num_pages))))
#define MINOR_INDEX(bloomfilt, key, config_index) ((unsigned int) HASH(key, bloomfilt->hash_configs[config_index], PAGE_SIZE_BITS))
#define GET_SUBFILTER(bloomfilt, key)             ((byte_t *)     ( (byte_t *) bloomfilt->bitarr + MAJOR_INDEX(bloomfilt, key)*PAGE_SIZE_BYTES))

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
