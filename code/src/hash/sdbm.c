#include "hash.h"

hash_t hash(char *str, hash_config_t seed) {
    hash_t hash = 0;
    unsigned long c = seed;

    do {
        hash = c + (hash << 6) + (hash << 16) - hash;
    } while (c = *str++);

    return hash;
}

hash_config_t generate_hash_config() {
    return rand() + ((long) rand()) << sizeof(int);
}
