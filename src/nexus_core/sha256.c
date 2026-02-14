#include "sha256.h"

void sha256_hash(const uint8_t *data, size_t len, char *out)
{
    if (!data || !out)
        return;

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(data, len, hash);

    static const char hex[] = "0123456789abcdef";

    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        out[i * 2]     = hex[(hash[i] >> 4) & 0xF];
        out[i * 2 + 1] = hex[hash[i] & 0xF];
    }

    out[SHA256_DIGEST_LENGTH * 2] = '\0';
}
