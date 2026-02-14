#ifndef NEXUS_WALLET_SECP256K1_FILE_H
#define NEXUS_WALLET_SECP256K1_FILE_H

#include "util.h"
#include "secp256k1_key.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *filename;
    int created_at;
} SECP256K1_Keyfile;

/**
 * @brief Opens the .dat keyfile that stores/loads the private key.
 *
 * @param filename
 * @return
 */
SECP256K1_Keyfile open_secp256k1_keyfile(const char *filename);

/**
 * @brief Saves the private key associated with the keypair to a .dat file (SECP256K1_Keyfile).
 *
 * @param keyfile
 * @param keypair
 * @return
 */
int save_secp256k1_private_key(SECP256K1_Keyfile keyfile, SECP256K1_Keypair keypair);

/**
 * @brief Loads the private key from SECP256K1_Keyfile
 *
 * @param keyfile
 * @param out
 */
void load_secp256k1_private_key(SECP256K1_Keyfile keyfile, uint8_t *out);

#endif // NEXUS_WALLET_SECP256K1_FILE_H
