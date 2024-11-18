#include <iostream>
#include <cmath>
#include <random>
using namespace std;

class ElGamal {
private:
    // System parameters
    long long p;  // Prime number
    long long g;  // Generator
    // Private key
    long long x;  // Random number < p
    // Public key
    long long y;  // y = g^x mod p
    
    long long power_mod(long long base, long long exp, long long mod) {
        long long result = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp & 1)
                result = (result * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }

public:
    ElGamal() {
        // Using small numbers for demonstration
        p = 23;  // Prime number
        g = 5;   // Generator
        x = 6;   // Private key
        y = power_mod(g, x, p);  // Public key = g^x mod p
        
        cout << "ElGamal Parameters:\n";
        cout << "Prime (p): " << p << "\n";
        cout << "Generator (g): " << g << "\n";
        cout << "Public key (y): " << y << "\n\n";
    }

    pair<long long, long long> encrypt(long long message) {
        // Generate random k
        long long k = 4;  // Usually random, fixed for demonstration
        
        // Calculate c1 = g^k mod p
        long long c1 = power_mod(g, k, p);
        
        // Calculate c2 = m * y^k mod p
        long long c2 = (message * power_mod(y, k, p)) % p;
        
        cout << "Encrypting message: " << message << "\n";
        cout << "c1: " << c1 << ", c2: " << c2 << "\n";
        
        return make_pair(c1, c2);
    }

    long long decrypt(pair<long long, long long> cipher) {
        long long c1 = cipher.first;
        long long c2 = cipher.second;
        
        // Calculate s = c1^x mod p
        long long s = power_mod(c1, x, p);
        
        // Calculate s^(p-2) mod p (modular multiplicative inverse)
        long long s_inv = power_mod(s, p-2, p);
        
        // m = c2 * s^(p-2) mod p
        long long m = (c2 * s_inv) % p;
        
        cout << "Decrypting (c1=" << c1 << ", c2=" << c2 << "): " << m << "\n";
        
        return m;
    }
};

int main() {
    ElGamal crypto;
    
    // Example message (must be less than p)
    long long message = 12;
    cout << "Original message: " << message << "\n\n";
    
    // Encrypt
    auto encrypted = crypto.encrypt(message);
    
    // Decrypt
    long long decrypted = crypto.decrypt(encrypted);
    
    cout << "\nDecrypted message: " << decrypted << "\n";
    
    return 0;
}