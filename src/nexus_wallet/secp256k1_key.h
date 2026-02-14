#ifndef NEXUS_WALLET_SECP256K1_KEY_H
#define NEXUS_WALLET_SECP256K1_KEY_H

#include "util.h"
#include "sha256.h"
#include <secp256k1.h>
#include <stdio.h>
#include <stdlib.h>

#define PRIVATE_KEY_LENGTH 32
#define PUBLIC_KEY_COMPRESSED_LENGTH 33

#define SIGNATURE_LENGTH 64

typedef struct {
    uint8_t private_key[PRIVATE_KEY_LENGTH];
    uint8_t public_key[PUBLIC_KEY_COMPRESSED_LENGTH];
} SECP256K1_Keypair;

/**
 * @brief Generates a cryptographic keypair using /dev/urandom & libsecp256k1.
 *
 * @param ctx
 * @return
 */
SECP256K1_Keypair generate_secp256k1_keypair(const secp256k1_context *ctx);

/**
 * @brief Signs data using secp256k1 keypair.
 *
 * @param ctx
 * @param private_key
 * @param msg32
 * @param sig64
 * @return
 */
int sign_using_secp256k1_private_key(
    const secp256k1_context *ctx,
    const uint8_t private_key[PRIVATE_KEY_LENGTH],
    const uint8_t msg32[SHA256_HASH_LENGTH],
    uint8_t sig64[SIGNATURE_LENGTH]
);

#endif // NEXUS_WALLET_SECP256K1_KEY_H
