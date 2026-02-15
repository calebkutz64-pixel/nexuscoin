#include "secp256k1_key.h"

SECP256K1_Keypair generate_secp256k1_keypair(const secp256k1_context *ctx)
{
    SECP256K1_Keypair keypair;

    do {
        if (!secure_random(keypair.private_key, sizeof(keypair.private_key))) {
            fprintf(stderr, "Random generation failed.\n");
            exit(1);
        }
    } while (!secp256k1_ec_seckey_verify(ctx, keypair.private_key));

    secp256k1_pubkey pubkey;
    if (!secp256k1_ec_pubkey_create(ctx, &pubkey, keypair.private_key)) {
        fprintf(stderr, "Public key creation failed.\n");
        exit(1);
    }

    size_t pubkey_len = PUBLIC_KEY_COMPRESSED_LENGTH;

    secp256k1_ec_pubkey_serialize(
        ctx,
        keypair.public_key,
        &pubkey_len,
        &pubkey,
        SECP256K1_EC_COMPRESSED
    );

    return keypair;
}

int sign_using_secp256k1_private_key(
    const secp256k1_context *ctx,
    const uint8_t private_key[PRIVATE_KEY_LENGTH],
    const uint8_t msg32[SHA256_HASH_LENGTH],
    uint8_t sig64[SIGNATURE_LENGTH])
{
    if (!ctx || !private_key || !msg32 || !sig64)
    {
        return 0;
    }

    int ret = 0;
    secp256k1_ecdsa_signature signature;

    if (!secp256k1_ec_seckey_verify(ctx, private_key))
    {
        return 0;
    }

    ret = secp256k1_ecdsa_sign(
        ctx,
        &signature,
        msg32,
        private_key,
        NULL,
        NULL
    );

    if (!ret)
    {
        return 0;
    }

    secp256k1_ecdsa_signature_serialize_compact(
        ctx,
        sig64,
        &signature
    );

    return 1;
}
