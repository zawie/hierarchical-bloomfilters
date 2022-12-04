#include "hash.h"

hash_t hash(char *str, hash_config_t seed) {
    hash_t hash = 5381;
    unsigned long c = seed;

    do {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    } while (c = *str++);

    return hash % 2147483647;
}

hash_config_t generate_hash_config() {
    return rand() + ((long) rand()) << sizeof(int);
}
