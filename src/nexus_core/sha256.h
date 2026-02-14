#ifndef NEXUS_CORE_SHA256_H
#define NEXUS_CORE_SHA256_H

#include "util.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>

#define SHA256_HASH_LENGTH 32
#define SHA256_CHAR_OUT_LENGTH 65

/**
 * @brief Takes input data (uint8_t *) and hashes it using sha256 hash algorithm.
 *
 * @param data
 * @param len
 * @param out
 */
void sha256_hash(const uint8_t *data, size_t len, char *out);

#endif // NEXUS_CORE_SHA256_H
