// Row-column transposition cipher.

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

string removeSpaces(const string& str) {
    string result = str;
    result.erase(remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

// New function to get filler character
char getFillerChar(int index) {
    const string fillers = "XYZWPQ";
    return fillers[index % fillers.length()];
}

string encrypt(const string& plaintext, int key) {
    int rows = ceil(static_cast<double>(plaintext.length()) / key);
    vector<vector<char>> grid(rows, vector<char>(key));

    int index = 0;
    int fillerIndex = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < key; ++j) {
            if (index < plaintext.length()) {
                grid[i][j] = plaintext[index++];
            } else {
                grid[i][j] = getFillerChar(fillerIndex++);
            }
        }
    }
    
    string ciphertext;
    for (int j = 0; j < key; ++j) {
        for (int i = 0; i < rows; ++i) {
            ciphertext += grid[i][j];
        }
    }
    
    cout << "Encryption grid:\n";
    for (const auto& row : grid) {
        for (char c : row) {
            cout << c << ' ';
        }
        cout << "\n";
    }
    
    return ciphertext;
}

string decrypt(const string& ciphertext, int key) {
    int rows = ceil(static_cast<double>(ciphertext.length()) / key);
    vector<vector<char>> grid(rows, vector<char>(key));
    
    int index = 0;
    for (int j = 0; j < key; ++j) {
        for (int i = 0; i < rows; ++i) {
            grid[i][j] = ciphertext[index++];
        }
    }
    
    string plaintext;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < key; ++j) {
            plaintext += grid[i][j];
        }
    }
    
    cout << "Decryption grid:\n";
    for (const auto& row : grid) {
        for (char c : row) {
            cout << c << ' ';
        }
        cout << "\n";
    }
    
    return plaintext;
}

int main()
{
    string plaintext;
    int key;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
    cout << "Enter the key (number of columns): ";
    cin >> key;
    
    plaintext = removeSpaces(plaintext);
    
    cout << "Plaintext (without spaces): " << plaintext << "\n";
    cout << "Key: " << key << "\n";

    string ciphertext = encrypt(plaintext, key);
    cout << "Ciphertext: " << ciphertext << "\n";

    string decrypted = decrypt(ciphertext, key);
    cout << "Decrypted: " << decrypted << "\n";

    return 0;   
}