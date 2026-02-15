#ifndef NEXUS_H
#define NEXUS_H

// CORE
#include "nexus_core/sha256.h"
#include "nexus_core/util.h"

// WALLET
#include "nexus_wallet/secp256k1_file.h"
#include "nexus_wallet/secp256k1_key.h"

#include <string.h>

// CLI modules
static int module_keygen(int argc, char **argv)
{
    const char *out_path = NULL;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--out") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Missing value for --out\n");
                return 0;
            }
            out_path = argv[i + 1];
            i++;
        }
        else
        {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            return 0;
        }
    }

    if (!out_path)
    {
        fprintf(stderr, "--out is required\n");
        return 0;
    }

    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);

    SECP256K1_Keypair keypair = generate_secp256k1_keypair(ctx);
    SECP256K1_Keyfile keyfile = open_secp256k1_keyfile(out_path);

    if (!save_secp256k1_private_key(keyfile, keypair))
    {
        fprintf(stderr, "Failed to save secp256k1 private key to %s\n", out_path);
        return 0;
    }

    printf("SECP256K1 key generated & saved to %s\n", out_path);

    secp256k1_context_destroy(ctx);
    return 1;
}

static int module_sign(int argc, char **argv)
{
    const char *in_path = NULL;
    const char *msg = NULL;

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "--in") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Missing value for --in\n");
                return 0;
            }
            in_path = argv[++i];
        }
        else if (strcmp(argv[i], "--msg") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Missing value for --msg\n");
                return 0;
            }
            msg = argv[++i];
        }
        else
        {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            return 0;
        }
    }

    if (!in_path || !msg)
    {
        fprintf(stderr, "--in and --msg required\n");
        return 0;
    }

    SECP256K1_Keyfile keyfile;
    keyfile.filename = in_path;
    keyfile.created_at = 0;

    uint8_t private_key[PRIVATE_KEY_LENGTH];

    load_secp256k1_private_key(keyfile, private_key);

    /* Hash message */
    uint8_t msg_hash[SHA256_HASH_LENGTH];
    sha256((const uint8_t *)msg, strlen(msg), msg_hash);

    /* Create context */
    secp256k1_context *ctx =
        secp256k1_context_create(SECP256K1_CONTEXT_SIGN);

    if (!ctx)
    {
        fprintf(stderr, "Failed to create secp256k1 context\n");
        return 0;
    }

    /* Verify key */
    if (!secp256k1_ec_seckey_verify(ctx, private_key))
    {
        fprintf(stderr, "Invalid private key\n");
        secp256k1_context_destroy(ctx);
        return 0;
    }

    uint8_t sig[SIGNATURE_LENGTH];

    if (!sign_using_secp256k1_private_key(
            ctx,
            private_key,
            msg_hash,
            sig))
    {
        fprintf(stderr, "Signing failed\n");
        secp256k1_context_destroy(ctx);
        return 0;
    }

    printf("Signed | ");
    print_hex(sig, SIGNATURE_LENGTH);

    secp256k1_context_destroy(ctx);
    return 1;
}

#endif // NEXUS_H
