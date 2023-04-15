#include "AES.cpp"

void EncryptCTR(const unsigned char in[], unsigned char out[], unsigned int len, const unsigned char key[], const unsigned char iv[]) {
    unsigned char block[16];
    unsigned char counter[16];
    unsigned char roundKeys[176];
    unsigned int counter_len = 0;
    KeyExpansion(key, roundKeys);

    // Copy IV to counter
    memcpy(counter, iv, 16);

    for (unsigned int i = 0; i < len; i++) {
        // Check if counter needs to be incremented
        if (counter_len == 16) {
            counter_len = 0;
            EncryptBlock(counter, counter, roundKeys);
            for (int j = 15; j >= 0; j--) {
                if (++counter[j]) {
                    break;
                }
            }
        }

        // XOR input with counter to generate keystream
        block[0] = in[i] ^ counter[counter_len++];

        // Encrypt the block with the keystream
        EncryptBlock(block, block, roundKeys);

        // Copy encrypted block to output
        out[i] = block[0];
    }
}

void DecryptCTR(const unsigned char in[], unsigned char out[], unsigned int len, const unsigned char key[], const unsigned char iv[]) {
    // CTR mode is symmetrical, so encryption and decryption are the same
    EncryptCTR(in, out, len, key, iv);
}

int main() {
    // Input plaintext and key
    const unsigned char plaintext[] = "Hello, AES-CTR!";
    const unsigned char key[] = "ThisIsASecretKey";

    // IV (Initialization Vector)
    const unsigned char iv[] = "ThisIsAnIV12345";

    // Determine the length of the plaintext
    unsigned int len = strlen((const char*)plaintext);

    // Allocate memory for ciphertext and decrypted text
    unsigned char* ciphertext = (unsigned char*)malloc(len * sizeof(unsigned char));
    unsigned char* decryptedtext = (unsigned char*)malloc(len * sizeof(unsigned char));

    // Encrypt the plaintext using AES-CTR
    EncryptCTR(plaintext, ciphertext, len, key, iv);

    // Print the ciphertext
    printf("Ciphertext: ");
    for (unsigned int i = 0; i < len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext using AES-CTR
    DecryptCTR(ciphertext, decryptedtext, len, key, iv);

    // Null-terminate the decrypted text
    decryptedtext[len] = '\0';

    // Print the decrypted text
    printf("Decrypted Text: %s\n", decryptedtext);


    // Free dynamically allocated memory
    free(ciphertext);
    free(decryptedtext);

    return 0;
}