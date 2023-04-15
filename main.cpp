#include <iostream>
#include <cstring>
#include <openssl/aes.h>

void print_hex(const unsigned char* buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
}

int main() {
    // AES-128 key (16 bytes)
    unsigned char key[] = {
        0x2b, 0x7e, 0x15, 0x16,
        0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88,
        0x09, 0xcf, 0x4f, 0x3c
    };

    // AES-CCMP nonce (13 bytes)
    unsigned char nonce[] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c
    };

    // Plain text data (16 bytes)
    unsigned char plaintext[] = "Hello, AES-CCMP!";

    // AES-CCMP ciphertext and authentication tag
    unsigned char ciphertext[sizeof(plaintext)] = { 0 };
    unsigned char tag[AES_BLOCK_SIZE] = { 0 };

    // AES-CCMP decryption buffer
    unsigned char decrypted[sizeof(plaintext)] = { 0 };

    // Set up AES-CCMP encryption context
    AES_KEY aes_key;
    AES_ccm128_init(&aes_key, sizeof(key), key, sizeof(nonce), nonce, AES_BLOCK_SIZE * 8, AES_BLOCK_SIZE * 8);

    // Encrypt the plaintext
    AES_ccm128_encrypt(plaintext, ciphertext, sizeof(plaintext), &aes_key, NULL, 0, tag);

    // Print the ciphertext and authentication tag
    printf("Ciphertext: ");
    print_hex(ciphertext, sizeof(ciphertext));
    printf("Tag: ");
    print_hex(tag, sizeof(tag));

    // Set up AES-CCMP decryption context
    AES_ccm128_init(&aes_key, sizeof(key), key, sizeof(nonce), nonce, AES_BLOCK_SIZE * 8, AES_BLOCK_SIZE * 8);

    // Decrypt the ciphertext
    AES_ccm128_decrypt(ciphertext, decrypted, sizeof(ciphertext), &aes_key, NULL, 0, tag);

    // Print the decrypted plaintext
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
