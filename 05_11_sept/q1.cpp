// 1. Write a program to encrypt the message "Are you Ready for class" using shift cipher with any key value. Then decrypt the message back to plain text.

#include <bits/stdc++.h>

using namespace std;

// Function to encrypt a message using shift cipher
string encrypt(const string &message, int key)
{
    string encrypted_message = "";
    for (char c : message)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            encrypted_message += static_cast<char>((c - base + key) % 26 + base);
        }
        else if (isdigit(c))
        {
            encrypted_message += static_cast<char>((c - '0' + key) % 10 + '0');
        }
        else
        {
            encrypted_message += c;
        }
    }
    return encrypted_message;
}

// Function to decrypt a message encrypted with shift cipher
string decrypt(const string &encrypted_message, int key)
{
    string decrypted_message = "";
    for (char c : encrypted_message)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            decrypted_message += static_cast<char>((c - base - key + 26) % 26 + base);
        }
        else if (isdigit(c))
        {
            decrypted_message += static_cast<char>((c - '0' - key + 10) % 10 + '0');
        }
        else
        {
            decrypted_message += c;
        }
    }
    return decrypted_message;
}

int main()
{
    string original_message;
    cout << "Enter the message to encrypt: ";
    getline(cin, original_message);
    int key;
    cout << "Enter the key value: ";
    cin >> key;

    // Encrypt the message
    string encrypted_message = encrypt(original_message, key);

    // Decrypt the message
    string decrypted_message = decrypt(encrypted_message, key);

    // Output results
    cout << "Original message: " << original_message << "\n";
    cout << "Encrypted message: " << encrypted_message << "\n";
    cout << "Decrypted message: " << decrypted_message << "\n";

    return 0;
}