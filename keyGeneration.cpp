#include <iostream>
#include <string>
#include <random>
#include <chrono>

using namespace std;

// Function to generate a random string of given length
string generateRandomString(int length) {
    static const char characters[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(0, sizeof(characters) - 2);

    string randomString;
    randomString.reserve(length);
    for (int i = 0; i < length; ++i) {
        randomString += characters[distribution(rng)];
    }

    return randomString;
}

// unsigned char* generateRandomKey() {
//     string key = generateRandomString(16);
//     unsigned char keyArray[16];
//     for (int i = 0; i < 16; ++i) {
//         keyArray[i] = key[i];
//     }
//     return keyArray;
// }