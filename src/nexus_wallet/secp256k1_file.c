#include "secp256k1_file.h"

#include <time.h>

SECP256K1_Keyfile open_secp256k1_keyfile(const char *filename)
{
    SECP256K1_Keyfile keyfile;
    keyfile.filename = filename;
    keyfile.created_at = (int)time(NULL);

    FILE *fp = fopen(keyfile.filename, "wb");
    if (!fp)
    {
        fprintf(stderr, "Failed to open keyfile for writing.\n");
        exit(1);
    }

    fclose(fp);

    return keyfile;
}

int save_secp256k1_private_key(SECP256K1_Keyfile keyfile, SECP256K1_Keypair keypair)
{
    if (!keyfile.filename)
    {
        printf("Using default filename (signingkey-<time-created>.dat) for private keyfile.\n");
        sprintf(keyfile.filename, "signingkey-%d", keyfile.created_at);
    }

    FILE *fp = fopen(keyfile.filename, "wb");
    if (!fp)
    {
        fprintf(stderr, "Failed to open keyfile for writing.\n");
        return 0;
    }

    fwrite(keypair.private_key, PRIVATE_KEY_LENGTH, 1, fp);

    fclose(fp);

    return 1;
}

void load_secp256k1_private_key(SECP256K1_Keyfile keyfile, uint8_t *out)
{
    if (!keyfile.filename)
    {
        printf("No filename supplied for load_secp256k1_private_key");
        exit(1);
    }

    FILE *fp = fopen(keyfile.filename, "rb");
    if (!fp)
    {
        fprintf(stderr, "Failed to open keyfile for reading.\n");
        exit(1);
    }

    if (fread(out, 1, PRIVATE_KEY_LENGTH, fp) != 32)
    {
        fprintf(stderr, "Failed to read private key from SECP256K1_Keyfile");
        exit(1);
    }

    fclose(fp);
}
