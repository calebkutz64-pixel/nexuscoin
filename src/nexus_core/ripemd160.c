#include "ripemd160.h"

void ripemd160(const uint8_t *data, size_t len, uint8_t out[RIPEMD160_HASH_LENGTH])
{
    RIPEMD160(data, len, out);
}
