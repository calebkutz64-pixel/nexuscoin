#include "base58.h"

size_t base58_encode(const uint8_t *data, size_t len, char *out)
{
    if (len == 0)
        return 0;

    size_t zeros = 0;
    while (zeros < len && data[zeros] == 0)
        zeros++;

    size_t size = len * 138 / 100 + 1;
    uint8_t *b58 = calloc(size, 1);
    if (!b58)
        return 0;

    size_t i, j, high = size - 1;

    for (i = zeros; i < len; i++) {
        uint32_t carry = data[i];

        for (j = size - 1; j > high || carry; j--) {
            carry += 256 * b58[j];
            b58[j] = carry % 58;
            carry /= 58;
        }

        high = j;
    }

    i = 0;
    while (i < size && b58[i] == 0)
        i++;

    size_t out_len = 0;

    for (j = 0; j < zeros; j++)
        out[out_len++] = '1';

    while (i < size)
        out[out_len++] = BASE58_ALPHABET[b58[i++]];

    out[out_len] = '\0';

    free(b58);
    return out_len;
}
