#include <iostream>
#include <string>
#include "cryptopp870/aes.h"
#include "cryptopp870/ccm.h"
#include "cryptopp870/osrng.h"
#include "cryptopp870/hex.h"
#include "cryptopp870/filters.h"
#include "cryptopp870/fipsalgt.cpp"
#include "cryptopp870/files.h"

using namespace CryptoPP;
int main()
{
    using namespace CryptoPP;

    // Generate a random key and nonce
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());

    byte nonce[AES::BLOCKSIZE];
    prng.GenerateBlock(nonce, sizeof(nonce));

    // Data to be encrypted
    std::string plaintext = "Hello, AES-CCMP!";
    std::string ciphertext;
    std::string decryptedtext;

    try
    {
        // Encryption
        CCM< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), nonce, sizeof(nonce));

        StringSource(plaintext, true,
            new AuthenticatedEncryptionFilter(e,
                new StringSink(ciphertext)
            ) // AuthenticatedEncryptionFilter
        ); // StringSource

        std::cout << "Plaintext: " << plaintext << std::endl;
        std::cout << "Ciphertext (hex): ";
        StringSource(ciphertext, true,
            new HexEncoder(
                new FileSink(std::cout)
            ) // HexEncoder
        ); // StringSource
        std::cout << std::endl;

        // Decryption
        CCM< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), nonce, sizeof(nonce));

        StringSource(ciphertext, true,
            new AuthenticatedDecryptionFilter(d,
                new StringSink(decryptedtext)
            ) // AuthenticatedDecryptionFilter
        ); // StringSource

        std::cout << "Decrypted text: " << decryptedtext << std::endl;
    }
    catch (const Exception& e)
    {
        std::cerr << "Crypto++ exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}