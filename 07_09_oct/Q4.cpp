// iv. Rail-fence cipher.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void printGrid(const vector<string>& rails) {
    for (const auto& rail : rails) {
        cout << rail << "\n";
    }
    cout << "\n";
}

string removeSpaces(const string& str) {
    string result = str;
    result.erase(remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

string encrypt(const string& plaintext, int key) {
    vector<string> rails(key, string(plaintext.length(), '.'));
    int rail = 0;
    bool down = true;

    for (size_t i = 0; i < plaintext.length(); ++i) {
        rails[rail][i] = plaintext[i];
        if (rail == 0) {
            down = true;
        } else if (rail == key - 1) {
            down = false;
        }
        rail += down ? 1 : -1;
    }

    cout << "Final encryption grid:\n";
    printGrid(rails);

    string ciphertext;
    for (const auto& rail : rails) {
        for (char c : rail) {
            if (c != '.') ciphertext += c;
        }
    }
    return ciphertext;
}

string decrypt(const string& ciphertext, int key) {
    vector<string> rails(key, string(ciphertext.length(), '.'));
    int rail = 0;
    bool down = true;

    for (size_t i = 0; i < ciphertext.length(); ++i) {
        rails[rail][i] = '*';
        if (rail == 0) {
            down = true;
        } else if (rail == key - 1) {
            down = false;
        }
        rail += down ? 1 : -1;
    }

    int index = 0;
    for (auto& rail : rails) {
        for (char& c : rail) {
            if (c == '*') c = ciphertext[index++];
        }
    }

    cout << "Final decryption grid:\n";
    printGrid(rails);

    string plaintext(ciphertext.length(), ' ');
    rail = 0;
    down = true;
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        plaintext[i] = rails[rail][i];
        if (rail == 0) {
            down = true;
        } else if (rail == key - 1) {
            down = false;
        }
        rail += down ? 1 : -1;
    }

    return plaintext;
}

int main() {
    string plaintext;
    int key;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
    plaintext = removeSpaces(plaintext);

    cout << "Enter the key (number of rails): ";
    cin >> key;

    cout << "\nEncrypting...\n";
    string ciphertext = encrypt(plaintext, key);
    cout << "Encrypted text: " << ciphertext << "\n";

    cout << "\nDecrypting...\n";
    string decrypted = decrypt(ciphertext, key);
    cout << "Decrypted text: " << decrypted << "\n";

    return 0;
}