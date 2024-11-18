#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random substitution key
string generateKey() {
    string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(time(0));  // Seed the random number generator
    for (int i = 25; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(key[i], key[j]);
    }
    return key;
}

// Function to encrypt a message using substitution cipher
string encrypt(const string& message, const string& key) {
    string encrypted_message = "";
    for (char c : message) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            encrypted_message += isupper(c) ? key[c - 'A'] : tolower(key[c - 'a']);
        } else {
            encrypted_message += c;
        }
    }
    return encrypted_message;
}

// Function to decrypt a message encrypted with substitution cipher
string decrypt(const string& encrypted_message, const string& key) {
    string decrypted_message = "";
    for (char c : encrypted_message) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            size_t index = key.find(toupper(c));
            decrypted_message += (base == 'A') ? 'A' + index : 'a' + index;
        } else {
            decrypted_message += c;
        }
    }
    return decrypted_message;
}

int main() {
    const string original_message = "Are you Ready for class";
    string key = generateKey();

    // Encrypt the message
    string encrypted_message = encrypt(original_message, key);

    // Decrypt the message
    string decrypted_message = decrypt(encrypted_message, key);

    // Output results
    cout << "Original message: " << original_message << "\n";
    cout << "Key: " << key << "\n";
    cout << "Encrypted message: " << encrypted_message << "\n";
    cout << "Decrypted message: " << decrypted_message << "\n";

    return 0;
}