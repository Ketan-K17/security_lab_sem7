// RSA with signature

#include <bits/stdc++.h>
using namespace std;

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    
    if (m == 1)
        return 0;
    
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    
    if (x < 0)
        x += m0;
    
    return x;
}

long long mod_pow(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;
    
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent = exponent >> 1;
    }
    
    return result;
}

class RSA {
private:
    long long p, q;      // Prime numbers
    long long n;         // Modulus n = p * q
    long long phi;       // Euler's totient = (p-1) * (q-1)
    long long e;         // Public exponent
    long long d;         // Private exponent

public:
    RSA(long long prime1 = 61, long long prime2 = 53) {
        cout << "Initializing RSA with p=" << prime1 << " and q=" << prime2 << endl;
        
        p = prime1;
        q = prime2;
        
        n = p * q;
        phi = (p - 1) * (q - 1);
        
        // Choose e
        e = 17;
        while (gcd(e, phi) != 1) {
            e += 2;
        }
        
        // Calculate private key d
        d = mod_inverse(e, phi);
        
        cout << "Public Key (e,n): (" << e << "," << n << ")" << endl;
        cout << "Private Key (d,n): (" << d << "," << n << ")" << endl;
    }
    
    // Original encryption/decryption methods
    long long encrypt(long long message) {
        cout << "Encrypting message: " << message << endl;
        return mod_pow(message, e, n);
    }
    
    long long decrypt(long long ciphertext) {
        cout << "Decrypting ciphertext: " << ciphertext << endl;
        return mod_pow(ciphertext, d, n);
    }
    
    // New signature methods
    long long sign(long long message) {
        cout << "Signing message: " << message << endl;
        // In RSA, signing is essentially encrypting with the private key
        long long signature = mod_pow(message, d, n);
        cout << "Generated signature: " << signature << endl;
        return signature;
    }
    
    bool verify(long long message, long long signature) {
        cout << "Verifying signature for message: " << message << endl;
        cout << "With signature: " << signature << endl;
        
        // Log the public key used for verification
        cout << "Using public key (e, n): (" << e << ", " << n << ")" << endl;
        
        // In RSA, verification is done by "decrypting" the signature with public key
        long long decoded = mod_pow(signature, e, n);
        
        // Log the decoded message
        cout << "Decoded message from signature: " << decoded << endl;
        
        // Compare the decoded message with the original message
        bool is_valid = (decoded == message);
        
        // Log the result of the comparison
        cout << "Original message: " << message << endl;
        cout << "Decoded message: " << decoded << endl;
        cout << "Signature is " << (is_valid ? "valid" : "invalid") << endl;
        
        return is_valid;
    }
    
    pair<long long, long long> get_public_key() {
        return make_pair(e, n);
    }
    
    pair<long long, long long> get_private_key() {
        return make_pair(d, n);
    }
};

int main() {
    RSA rsa(61, 53);
    
    // Example message
    long long message = 123;
    cout << "\n=== Encryption/Decryption Demo ===" << endl;
    cout << "Original Message: " << message << endl;
    
    // Encrypt and decrypt
    long long ciphertext = rsa.encrypt(message);
    cout << "Encrypted Message: " << ciphertext << endl;
    
    long long decrypted = rsa.decrypt(ciphertext);
    cout << "Decrypted Message: " << decrypted << endl;
    
    // Digital signature demo
    cout << "\n=== Digital Signature Demo ===" << endl;
    
    // Sign the message
    long long signature = rsa.sign(message);
    cout << "Generated signature: " << signature << endl;
    
    // Verify the signature
    bool is_valid = rsa.verify(message, signature);
    
    // Try verifying with a tampered message
    cout << "\n=== Tampering Demo ===" << endl;
    long long tampered_message = message + 1;
    cout << "Trying to verify signature with tampered message: " << tampered_message << endl;
    bool is_invalid = rsa.verify(tampered_message, signature);
    
    return 0;
}