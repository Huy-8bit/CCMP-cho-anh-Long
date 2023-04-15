#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<iomanip>

using namespace std;

string encrypt_block(string xor_result, string key) {
    int AES_BLOCK_SIZE = 16;

    char output_block[AES_BLOCK_SIZE];


    string repeated_key = key;
    while (repeated_key.length() < AES_BLOCK_SIZE) {
        repeated_key += key;
    }
    repeated_key = repeated_key.substr(0, AES_BLOCK_SIZE);


    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        output_block[i] = xor_result[i] ^ repeated_key[i];
    }


    string encrypted_block(output_block, AES_BLOCK_SIZE);

    return encrypted_block;
}

string CBCRandomEnc(string message, string key) {
    srand(time(0));
    int block_size = key.length();
    string iv = "0";
    // for (int i = 0; i < block_size; i++) {
    //     iv[i] = rand() % 256;
    // }
    string ciphertext;
    string prev_cipher_block = iv;
    int message_len = message.length();

    if (message_len % block_size != 0) {
        message += string(block_size - message_len % block_size, '\0');
        message_len = message.length();
    }

    for (int i = 0; i < message_len; i += block_size) {
        string plaintext_block = message.substr(i, block_size);

        string xor_result(block_size, ' ');
        for (int j = 0; j < block_size; j++) {
            xor_result[j] = plaintext_block[j] ^ prev_cipher_block[j];
        }

        string cipher_block = encrypt_block(xor_result, key);

        prev_cipher_block = cipher_block;

        ciphertext += cipher_block;
    }


    ciphertext = iv + ciphertext;
    return ciphertext;
}




int main() {
    char m[] = "Two One Nine Two", k[] = "Thats my Kung Fu";
    // print m (hexadecimal number)
    string c = CBCRandomEnc(m, k);
    // cout << c << endl;
    cout << "Ciphertext: ";
    cout << std::hex << std::setfill('0');
    for (int i = 0; i < c.length(); i++) {
        cout << std::setw(2) << (int)(unsigned char)c[i];
    }
    cout << endl;
    return 0;
}