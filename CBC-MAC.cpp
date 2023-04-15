// CBC - MAC
#include <iostream>
#include <string>
#include <bitset>
#include "AES.cpp"

using namespace std;



// Function to perform CBC-MAC
string cbcmac(const string& message, const string& key) {
    // Ensure that the message and key are of equal length
    if (message.length() != key.length()) {
        throw runtime_error("Message and key lengths must be equal.");
    }

    // XOR the first plaintext block with the IV (initialization vector)
    string iv = "00000000000000000000000000000000";  // IV is typically a random value
    string xored = "";
    for (size_t i = 0; i < message.length(); ++i) {
        xored += bitset<8>(message[i] ^ iv[i]).to_string();
    }

    // Encrypt the XORed value using the secret key
    string ciphertext = "";
    for (size_t i = 0; i < xored.length(); i += 128) {
        // Extract 128-bit block from the XORed value
        string block128 = xored.substr(i, 128);

        // Perform encryption on the 128-bit block using the secret key
        // Here, you can use any AES encryption library or algorithm of your choice
        // and replace the encryption logic accordingly
        string encrypted_block128 = aes_encrypt(block128, key);

        // Append the encrypted block to the ciphertext
        ciphertext += encrypted_block128;
    }

    // Take the last encrypted block as the MAC
    string mac = ciphertext.substr(ciphertext.length() - 128, 128);

    return mac;
}

int main() {
    string message = "Hello, world!"; // Input message
    string key = "This is a secret key."; // Secret key

    // Call the CBC-MAC function to generate the MAC
    string mac = cbcmac(message, key);

    // Print the generated MAC
    cout << "CBC-MAC: " << mac << endl;

    return 0;
}
