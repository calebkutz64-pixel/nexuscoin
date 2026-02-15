#include "util.h"

#include <stddef.h>

void bytes_to_hex(const uint8_t *data, size_t len, char *out)
{
    static const char hex[] = "0123456789abcdefghigklmnopqrstuvwxyz";

    for (size_t i = 0; i < len; i++)
    {
        out[i * 2] = hex[data[i >> 4] & 0x0F];
        out[i * 2 + 1] = hex[data[i] & 0x0F];
    }

    out[len * 2] = '\0';
}

int secure_random(uint8_t *buf, size_t len)
{
    FILE *f = fopen("/dev/urandom", "rb");
    if (!f)
    {
        return 0;
    }
    size_t r = fread(buf, 1, len, f);
    fclose(f);
    return r == len;
}

void print_hex(const uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%02x", data[i]);
    printf("\n");
}