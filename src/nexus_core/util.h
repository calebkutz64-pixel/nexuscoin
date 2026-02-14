#ifndef NEXUS_CORE_UTIL_H
#define NEXUS_CORE_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Convert uint8_t array (bytearray) to a printable hex version
 *
 * @param data
 * @param len
 * @param out
 */
void bytes_to_hex(const uint8_t *data, size_t len, char *out);

/**
 * @brief Uses /dev/urandom to generate random arbitrary data
 *
 * @param buf
 * @param len
 * @return
 */
int secure_random(uint8_t *buf, size_t len);

#endif // NEXUS_CORE_UTIL_H
