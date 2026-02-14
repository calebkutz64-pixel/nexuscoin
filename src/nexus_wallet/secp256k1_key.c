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
