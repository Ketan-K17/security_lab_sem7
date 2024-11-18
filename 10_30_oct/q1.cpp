#include <iostream>
#include <vector>
using namespace std;

class KnapsackCrypto {
private:
    vector<int> privateKey;  // Super-increasing sequence
    int modulus;
    int multiplier;
    vector<int> publicKey;

    // Helper function to calculate modular multiplicative inverse
    int modInverse(int a, int m) {
        for (int x = 1; x < m; x++) {
            if (((a % m) * (x % m)) % m == 1) {
                return x;
            }
        }
        return 1;
    }

public:
    KnapsackCrypto() {
        // Initialize with a simple super-increasing sequence
        privateKey = {2, 3, 7, 14, 30, 57, 120, 251};
        modulus = 491;  // Must be greater than sum of private key
        multiplier = 41; // Coprime with modulus
        
        cout << "Initializing Knapsack Cryptosystem\n";
        cout << "Private Key (super-increasing sequence): ";
        for (int x : privateKey) cout << x << " ";
        cout << "\nModulus: " << modulus;
        cout << "\nMultiplier: " << multiplier << "\n\n";

        // Generate public key
        publicKey.resize(privateKey.size());
        for (size_t i = 0; i < privateKey.size(); i++) {
            publicKey[i] = (privateKey[i] * multiplier) % modulus;
        }

        cout << "Generated Public Key: ";
        for (int x : publicKey) cout << x << " ";
        cout << "\n\n";
    }

    vector<int> encrypt(string message) {
        vector<int> encrypted;
        cout << "Encrypting message: " << message << "\n";

        for (char c : message) {
            int sum = 0;
            vector<int> binary = toBinary(c);
            
            cout << "Character '" << c << "' in binary: ";
            for (int bit : binary) cout << bit;
            cout << "\n";

            for (size_t i = 0; i < binary.size(); i++) {
                if (binary[i] == 1) {
                    sum += publicKey[i];
                }
            }
            encrypted.push_back(sum);
            cout << "Encrypted value: " << sum << "\n";
        }
        return encrypted;
    }

    string decrypt(vector<int> encrypted) {
        string decrypted;
        int inverse = modInverse(multiplier, modulus);
        
        cout << "\nDecrypting message using multiplicative inverse: " << inverse << "\n";

        for (int cipher : encrypted) {
            int sum = (cipher * inverse) % modulus;
            vector<int> binary = solveSubsetSum(sum);
            char c = fromBinary(binary);
            decrypted += c;
            
            cout << "Cipher: " << cipher << ", Binary: ";
            for (int bit : binary) cout << bit;
            cout << " -> '" << c << "'\n";
        }
        return decrypted;
    }

private:
    vector<int> toBinary(char c) {
        vector<int> binary(8, 0);
        for (int i = 7; i >= 0; i--) {
            binary[7-i] = (c >> i) & 1;
        }
        return binary;
    }

    char fromBinary(vector<int> binary) {
        char c = 0;
        for (size_t i = 0; i < binary.size(); i++) {
            if (binary[i]) {
                c |= (1 << (7-i));
            }
        }
        return c;
    }

    vector<int> solveSubsetSum(int sum) {
        vector<int> result(8, 0);
        for (int i = privateKey.size() - 1; i >= 0; i--) {
            if (sum >= privateKey[i]) {
                result[i] = 1;
                sum -= privateKey[i];
            }
        }
        return result;
    }
};

int main() {
    KnapsackCrypto crypto;
    
    string message = "helloworld";
    cout << "Original message: " << message << "\n\n";

    vector<int> encrypted = crypto.encrypt(message);
    cout << "\nFinal encrypted values: ";
    for (int x : encrypted) cout << x << " ";
    cout << "\n";

    string decrypted = crypto.decrypt(encrypted);
    cout << "\nDecrypted message: " << decrypted << "\n";

    return 0;
}