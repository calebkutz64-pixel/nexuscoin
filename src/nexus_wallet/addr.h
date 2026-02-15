#ifndef NEXUS_WALLET_ADDR_H
#define NEXUS_WALLET_ADDR_H

#include "sha256.h"
#include "ripemd160.h"
#include "secp256k1_key.h"
#include "base58.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define ADDR_BINARY_LENGTH 25

void create_public_key_address(
    const uint8_t public_key[PUBLIC_KEY_COMPRESSED_LENGTH],
    size_t len,
    char *out);

#endif // NEXUS_WALLET_ADDR_H
