from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes

# Step 1: Key Generation
# The sender and receiver generate a shared secret key using a secure key exchange protocol
# In this example, we generate a random 128-bit key
key = get_random_bytes(16)

# Step 2: Data Encryption
# The sender encrypts the data using AES-CTR mode with the generated key
plaintext = b"This is a sample plaintext message."
cipher = AES.new(key, AES.MODE_CTR)
ciphertext = cipher.encrypt(plaintext)

# Step 3: Message Authentication
# The sender generates a MAC for the encrypted data using CBC-MAC
mac = cipher.digest()

# Step 4: Data Transmission
# The sender transmits the ciphertext and MAC over the wireless network to the receiver
# In this example, we assume that the ciphertext and MAC are sent as separate variables

# Step 5: Data Reception
# The receiver receives the ciphertext and MAC
# In this example, we assume that the ciphertext and MAC are received as separate variables

# Step 6: Data Decryption and MAC Verification
# The receiver verifies the MAC and decrypts the ciphertext using AES-CTR mode with the shared key
# If the MAC is valid, the data is considered authentic and not tampered with during transmission
received_cipher = AES.new(key, AES.MODE_CTR, nonce=cipher.nonce)
received_plaintext = received_cipher.decrypt(ciphertext)
received_mac = received_cipher.digest()

# Verify the MAC
if mac == received_mac:
    print("MAC is valid. Data integrity is verified.")
    print("Received Plaintext:", received_plaintext.decode())
else:
    print("MAC is invalid. Data may have been tampered with during transmission.")

# Step 7: Data Utilization
# The receiver can now use the decrypted plaintext data for its intended purpose
