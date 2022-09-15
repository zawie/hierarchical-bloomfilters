#include "bloomfilter.h"
#include "bloomfilter.c"

#include "bitarr.h"
#include "bitarr.c"

#define INIT_BLOOM_FILTER() (bloomfilt_t * b = bloom_filter_init())
#define INSERT(key) (bloomfilter_insert(b, key))
#define CHECK(key) (bloomfilter_check(b,key) && bitarr_set(check_results, check_index++));