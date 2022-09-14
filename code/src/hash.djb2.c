#include "hash.h"

hash_t hash(char *str, hash_config_t seed) {
    hash_t hash = seed;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

hash_config_t generate_hash_config() {
    return rand() + ((long) rand()) << sizeof(int);
}