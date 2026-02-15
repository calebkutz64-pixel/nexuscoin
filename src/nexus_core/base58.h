#ifndef NEXUS_CORE_BASE58_H
#define NEXUS_CORE_BASE58_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static const char BASE58_ALPHABET[] =
    "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

/**
 * @brief Encodes data in bitcoins base58 format.
 *
 * @param data
 * @param len
 * @param out
 * @return
 */
size_t base58_encode(const uint8_t *data, size_t len, char *out);

#endif // NEXUS_CORE_BASE58_H
