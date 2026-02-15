#ifndef NEXUS_CORE_RIPEMD160_H
#define NEXUS_CORE_RIPEMD160_H

#include <openssl/ripemd.h>
#include <stdio.h>
#include <stdlib.h>

#define RIPEMD160_HASH_LENGTH 20

/**
 * @brief Ripemd160 hash function
 *
 * @param data
 * @param len
 * @param out
 */
void ripemd160(const uint8_t *data, size_t len, uint8_t out[RIPEMD160_HASH_LENGTH]);

#endif // NEXUS_CORE_RIPEMD160_H
