// Q3. Write a program to encrypt and decrypt the text using vigenere and vernam cipher.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string vigenereEncrypt(const string& plaintext, const string& key) {
    string ciphertext = plaintext;
    int keyLength = key.length();
    
    for (int i = 0; i < plaintext.length(); i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + key[i % keyLength] - 'A') % 26 + base;
        }
    }
    
    cout << "Vigenere Encryption: " << ciphertext << "\n";
    return ciphertext;
}

string vigenereDecrypt(const string& ciphertext, const string& key) {
    string plaintext = ciphertext;
    int keyLength = key.length();
    
    for (int i = 0; i < ciphertext.length(); i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - (key[i % keyLength] - 'A') + 26) % 26 + base;
        }
    }
    
    cout << "Vigenere Decryption: " << plaintext << "\n";
    return plaintext;
}

string vernamEncrypt(const string& plaintext, const string& key) {
    string ciphertext = plaintext;
    
    for (int i = 0; i < plaintext.length(); i++) {
        ciphertext[i] = plaintext[i] ^ key[i % key.length()];
    }
    
    cout << "Vernam Encryption: ";
    for (char c : ciphertext) {
        cout << hex << (int)c;
    }
    cout << "\n";
    
    return ciphertext;
}

string vernamDecrypt(const string& ciphertext, const string& key) {
    string plaintext = ciphertext;
    
    for (int i = 0; i < ciphertext.length(); i++) {
        plaintext[i] = ciphertext[i] ^ key[i % key.length()];
    }
    
    cout << "Vernam Decryption: " << plaintext << "\n";
    return plaintext;
}

int main() {
    string plaintext, key;
    
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    
    cout << "Enter key: ";
    getline(cin, key);
    
    cout << "\nVigenere Cipher:\n";
    string vigenereEncrypted = vigenereEncrypt(plaintext, key);
    vigenereDecrypt(vigenereEncrypted, key);
    
    cout << "\nVernam Cipher:\n";
    string vernamEncrypted = vernamEncrypt(plaintext, key);
    vernamDecrypt(vernamEncrypted, key);
    
    return 0;
}