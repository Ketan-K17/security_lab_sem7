// 2. Write a program to find the key value of the given cipher text (JBCRCLQRWCRVNBJENBWRWN)

#include <bits/stdc++.h>

using namespace std;

// Function to decrypt a message with a given key
string decrypt(const string& encrypted_message, int key) {
    string decrypted_message = "";
    for (char c : encrypted_message) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            decrypted_message += static_cast<char>((c - base - key + 26) % 26 + base);
        } else {
            decrypted_message += c;
        }
    }
    return decrypted_message;
}

// Function to calculate the frequency of each letter in a string
vector<int> calculateFrequency(const string& text) {
    vector<int> freq(26, 0);
    for (char c : text) {
        if (isalpha(c)) {
            freq[toupper(c) - 'A']++;
        }
    }
    return freq;
}

// Function to find the most likely key based on letter frequency
int findLikelyKey(const string& ciphertext) {
    vector<int> freq = calculateFrequency(ciphertext);
    int max_freq = *max_element(freq.begin(), freq.end());
    int most_common = distance(freq.begin(), find(freq.begin(), freq.end(), max_freq));
    
    // Assuming that 'E' is the most common letter in English
    return (most_common - ('E' - 'A') + 26) % 26;
}

int main() {
    const string ciphertext = "JBCRCLQRWCRVNBJENBWRWN";
    
    int likely_key = findLikelyKey(ciphertext);
    string decrypted = decrypt(ciphertext, likely_key);
    
    cout << "Ciphertext: " << ciphertext << "\n";
    cout << "Most likely key: " << likely_key << "\n";
    cout << "Decrypted message: " << decrypted << "\n";
    
    cout << "\nAll possible decryptions:\n";
    for (int key = 0; key < 26; key++) {
        cout << "Key " << key << ": " << decrypt(ciphertext, key) << "\n";
    }
    
    return 0;
}