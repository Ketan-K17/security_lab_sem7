// Elgamal with digital signature.

#include <iostream>
#include <cmath>
#include <random>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

class ElGamal {
private:
    // System parameters
    long long p;     // Prime number
    long long alpha; // Generator
    // Private key
    long long a;     // Private key
    // Public key
    long long beta;  // Public key (beta = alpha^a mod p)
    
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

public:
    ElGamal() {
        cout << "Enter prime number (p): ";
        cin >> p;
        cout << "Enter generator (alpha): ";
        cin >> alpha;
        cout << "Enter private key (a): ";
        cin >> a;
        beta = power_mod(alpha, a, p);  // Public key beta = alpha^a mod p
        
        cout << "ElGamal Parameters:\n";
        cout << "Prime (p): " << p << "\n";
        cout << "Generator (alpha): " << alpha << "\n";
        cout << "Private key (a): " << a << "\n";
        cout << "Public key (beta): " << beta << "\n\n";
    }

    pair<long long, long long> encrypt(long long message) {
        long long k = 4;  
        
        long long c1 = power_mod(alpha, k, p);
        long long c2 = (message * power_mod(beta, k, p)) % p;
        
        cout << "Encrypting message: " << message << "\n";
        cout << "c1: " << c1 << ", c2: " << c2 << "\n";
        
        return make_pair(c1, c2);
    }

    long long decrypt(pair<long long, long long> cipher) {
        long long c1 = cipher.first;
        long long c2 = cipher.second;
        
        long long s = power_mod(c1, a, p);
        long long s_inv = power_mod(s, p-2, p);
        long long m = (c2 * s_inv) % p;
        
        cout << "Decrypting (c1=" << c1 << ", c2=" << c2 << "): " << m << "\n";
        
        return m;
    }
    
    // Sign a message
    pair<long long, long long> sign(long long m) {
        long long k = 4;
        
        while (gcd(k, p-1) != 1) {
            k = (k + 1) % (p-1);
            if (k == 0) k = 1;
        }
        
        // gamma = alpha^k mod p
        long long gamma = power_mod(alpha, k, p);
        
        // k_inv = k^(-1) mod (p-1)
        long long k_inv = mod_inverse(k, p-1);
        
        // delta = (m - a*gamma)k^(-1) mod (p-1)
        long long delta = (k_inv * (m - a * gamma)) % (p-1);
        if (delta < 0) delta += (p-1);  
        
        cout << "Signing message: " << m << "\n";
        cout << "Signature components (gamma,delta): (" << gamma << "," << delta << ")\n";
        
        return make_pair(gamma, delta);
    }
    
    // Verify signature
    bool verify(long long m, pair<long long, long long> signature) {
        long long gamma = signature.first;
        long long delta = signature.second;
        
        cout << "Verifying signature for message: " << m << "\n";
        cout << "With signature (gamma,delta): (" << gamma << "," << delta << ")\n";
        
        if (gamma <= 0 || gamma >= p) {
            cout << "Verification failed: gamma out of range\n";
            return false;
        }
        
        // Verify: beta^gamma * gamma^delta ≡ alpha^m mod p
        long long right = (power_mod(beta, gamma, p) * power_mod(gamma, delta, p)) % p;
        long long left = power_mod(alpha, m, p);
        
        cout << "Verification calculation:\n";
        cout << "Left side (alpha^m mod p): " << left << "\n";
        cout << "Right side (beta^gamma * gamma^delta mod p): " << right << "\n";
        
        return left == right;
    }
};

int main() {
    ElGamal crypto;
    
    long long m = 12;
    cout << "Original message: " << m << "\n\n";
    
    cout << "=== Encryption/Decryption Demo ===\n";
    auto encrypted = crypto.encrypt(m);
    long long decrypted = crypto.decrypt(encrypted);
    cout << "Decrypted message: " << decrypted << "\n\n";
    
    cout << "=== Digital Signature Demo ===\n";
    auto signature = crypto.sign(m);
    bool is_valid = crypto.verify(m, signature);
    cout << "Signature is " << (is_valid ? "valid" : "invalid") << "\n\n";
    
    // Try verifying with a tampered message
    long long tampered_m = m + 1;
    cout << "Trying to verify tampered message: " << tampered_m << "\n";
    bool is_invalid = crypto.verify(tampered_m, signature);
    cout << "Tampered signature is " << (is_invalid ? "valid" : "invalid") << "\n";
    
    return 0;
}