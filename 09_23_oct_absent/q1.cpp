// Q1. IMPLEMENT THE DIFFIE-HELLMAN KEY EXCHANGE MECHANISM.

#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
using namespace std;

// Function for modular exponentiation (a^b mod p)
long long mod_pow(long long base, long long exponent, long long modulus) {
    cout << "\nCalculating: " << base << "^" << exponent << " mod " << modulus << endl;
    
    long long result = 1;
    base = base % modulus;
    
    while (exponent > 0) {
        // If exponent is odd, multiply base with result
        if (exponent & 1)
            result = (result * base) % modulus;
            
        // Exponent must be even now
        base = (base * base) % modulus;
        exponent = exponent >> 1; // Divide exponent by 2
    }
    
    cout << "Result: " << result << endl;
    return result;
}

// Generate a random private key
long long generate_private_key(long long min_val, long long max_val) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(min_val, max_val);
    return dis(gen);
}

class DiffieHellman {
private:
    long long p; // Prime modulus
    long long g; // Generator
    long long private_key;
    long long public_key;
    long long shared_secret;

public:
    // Constructor
    DiffieHellman(long long prime, long long generator) : p(prime), g(generator) {
        cout << "\nInitializing Diffie-Hellman with:" << endl;
        cout << "Prime (p): " << p << endl;
        cout << "Generator (g): " << g << endl;
    }

    void generate_keys() {
        // Generate private key
        private_key = generate_private_key(2, p-2);
        cout << "\nGenerated private key: " << private_key << endl;

        // Calculate public key: g^private_key mod p
        cout << "\nCalculating public key (g^private_key mod p):" << endl;
        public_key = mod_pow(g, private_key, p);
        cout << "Generated public key: " << public_key << endl;
    }

    long long get_public_key() const {
        return public_key;
    }

    void calculate_shared_secret(long long other_public_key) {
        cout << "\nCalculating shared secret with received public key: " << other_public_key << endl;
        shared_secret = mod_pow(other_public_key, private_key, p);
        cout << "Generated shared secret: " << shared_secret << endl;
    }

    // Get shared secret
    long long get_shared_secret() const {
        return shared_secret;
    }
};

int main() {
    long long p = 23;        // Prime modulus
    long long g = 5;         // Generator

    cout << "System Parameters: ";
    cout << "Prime (p): " << p << "; ";
    cout << "Generator (g): " << g << endl;

    // Create instances for Alice and Bob
    cout << "=== Alice's Setup ===" << endl;
    DiffieHellman alice(p, g);
    alice.generate_keys();

    cout << "=== Bob's Setup ===" << endl;
    DiffieHellman bob(p, g);
    bob.generate_keys();

    // Exchange public keys and calculate shared secret
    cout << "=== Key Exchange ===" << endl;
    cout << "Alice's public key: " << alice.get_public_key() << endl;
    cout << "Bob's public key: " << bob.get_public_key() << endl;

    cout << "=== Alice calculates shared secret ===" << endl;
    alice.calculate_shared_secret(bob.get_public_key());

    cout << "=== Bob calculates shared secret ===" << endl;
    bob.calculate_shared_secret(alice.get_public_key());

    // Verify that both parties have the same shared secret
    cout << "=== Verification ===" << endl;
    cout << "Alice's shared secret: " << alice.get_shared_secret() << endl;
    cout << "Bob's shared secret: " << bob.get_shared_secret() << endl;

    if (alice.get_shared_secret() == bob.get_shared_secret()) {
        cout << "Success! Shared secrets match." << endl;
    } else {
        cout << "Error! Shared secrets do not match." << endl;
    }

    // Show the mathematical steps
    cout << "=== Steps ===" << endl;
    cout << "1. Alice and Bob agree on p = " << p << " and g = " << g << endl;
    cout << "2. Alice chooses private key a, calculates A = g^a mod p" << endl;
    cout << "3. Bob chooses private key b, calculates B = g^b mod p" << endl;
    cout << "4. Alice calculates shared secret = B^a mod p" << endl;
    cout << "5. Bob calculates shared secret = A^b mod p" << endl;
    cout << "Both arrive at g^(ab) mod p" << endl;

    return 0;
}