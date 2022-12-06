#ifndef _HASH_H
#define _HASH_H

#define HASH_MOD(key, config, m) (hash(key, config) % m)

typedef unsigned long hash_config_t;
typedef unsigned long hash_t;

/**
 * Returns a hash value for a passed string
 * 
 * @param str a pointer to the string to hash; assumes null termination
 * @param config the hash configuration
 * @return a hash value
 */
hash_t hash(char *str, hash_config_t config);

/**
 * Psuedorandomly generate a hash config to be used by the hash function
 * 
 * @return a hash function configuration
 */
hash_config_t generate_hash_config();

#endif