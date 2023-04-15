#include <iostream>
#include <openssl/aes.h>
#include <openssl/rand.h>

using namespace std;

void CBCRandomEnc(string m, string k) {
    // Convert the plaintext message to bytes
    unsigned char *m_bytes = new unsigned char[m.length()];
    copy(m.begin(), m.end(), m_bytes);

    // Generate a random 16-byte initialization vector (IV)
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);

    // Convert the encryption key to bytes
    unsigned char *k_bytes = new unsigned char[k.length()];
    copy(k.begin(), k.end(), k_bytes);

    // Set up the AES cipher in CBC mode
    AES_KEY aes_key;
    AES_set_encrypt_key(k_bytes, 128, &aes_key);

    // Pad the message to the nearest multiple of the block size
    int padded_len = ((m.length() + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char *padded_m = new unsigned char[padded_len];
    memset(padded_m, 0, padded_len);
    memcpy(padded_m, m_bytes, m.length());

    // Encrypt the padded message using CBC mode
    unsigned char *ciphertext = new unsigned char[padded_len];
    AES_cbc_encrypt(padded_m, ciphertext, padded_len, &aes_key, iv, AES_ENCRYPT);

    // Print the ciphertext and IV
    cout << "Ciphertext: ";
    for (int i = 0; i < padded_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    cout << endl;

    cout << "IV: ";
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", iv[i]);
    }
    cout << endl;

    // Free memory
    delete[] m_bytes;
    delete[] k_bytes;
    delete[] padded_m;
    delete[] ciphertext;
}

int main() {
    string m = "Two One Nine Two";
    string k = "Thats my Kung Fu";

    CBCRandomEnc(m, k);

    return 0;
}
