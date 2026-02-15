#include "addr.h"

void create_public_key_address(
    const uint8_t public_key[PUBLIC_KEY_COMPRESSED_LENGTH],
    size_t len,
    char *out)
{
    uint8_t sha256_hash[SHA256_HASH_LENGTH];
    uint8_t ripemd160_hash[RIPEMD160_HASH_LENGTH];
    uint8_t versioned_payload[1 + RIPEMD160_HASH_LENGTH];
    uint8_t checksum_full[SHA256_HASH_LENGTH];
    uint8_t address_bin[ADDR_BINARY_LENGTH];

    sha256(public_key, len, sha256_hash);

    ripemd160(sha256_hash, SHA256_HASH_LENGTH, ripemd160_hash);

    versioned_payload[0] = 0x00;
    memcpy(versioned_payload + 1, ripemd160_hash, RIPEMD160_HASH_LENGTH);

    sha256(versioned_payload, sizeof(versioned_payload), checksum_full);
    sha256(checksum_full, SHA256_HASH_LENGTH, checksum_full);

    memcpy(address_bin, versioned_payload, sizeof(versioned_payload));
    memcpy(address_bin + sizeof(versioned_payload), checksum_full, 4);

    base58_encode(address_bin, ADDR_BINARY_LENGTH, out);
}
