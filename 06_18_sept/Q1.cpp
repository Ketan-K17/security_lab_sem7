// 1. Write a program to encrypt and decrypt the message "Meet Me at the Bridge" using Play fair cipher where key is "Your Name".

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char>> createMatrix(string key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    string alphabet = "abcdefghiklmnopqrstuvwxyz";
    key.erase(remove(key.begin(), key.end(), 'j'), key.end());
    key.erase(unique(key.begin(), key.end()), key.end());

    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (k < key.length()) {
                matrix[i][j] = key[k++];
                alphabet.erase(remove(alphabet.begin(), alphabet.end(), key[k-1]), alphabet.end());
            } else {
                matrix[i][j] = alphabet[0];
                alphabet.erase(alphabet.begin());
            }
        }
    }

    cout << "Matrix:\n";
    for (const auto& row : matrix) {
        for (char c : row) {
            cout << c << ' ';
        }
        cout << '\n';
    }

    return matrix;
}

pair<int, int> findPosition(vector<vector<char>>& matrix, char c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

string playfairEncrypt(string message, vector<vector<char>>& matrix) {
    string result;
    for (int i = 0; i < message.length(); i += 2) {
        char a = message[i];
        char b = (i + 1 < message.length()) ? message[i + 1] : 'x';
        if (a == b) b = 'x';

        pair<int, int> pos1 = findPosition(matrix, a);
        pair<int, int> pos2 = findPosition(matrix, b);

        cout << "Encrypting pair: " << a << b << " -> Positions: (" << pos1.first << "," << pos1.second << ") and (" << pos2.first << "," << pos2.second << ")\n";

        if (pos1.first == pos2.first) {
            result += matrix[pos1.first][(pos1.second + 1) % 5];
            result += matrix[pos2.first][(pos2.second + 1) % 5];
        } else if (pos1.second == pos2.second) {
            result += matrix[(pos1.first + 1) % 5][pos1.second];
            result += matrix[(pos2.first + 1) % 5][pos2.second];
        } else {
            result += matrix[pos1.first][pos2.second];
            result += matrix[pos2.first][pos1.second];
        }

        cout << "Encrypted pair: " << result[result.length() - 2] << result[result.length() - 1] << "\n";
    }
    return result;
}

string playfairDecrypt(string message, vector<vector<char>>& matrix) {
    string result;
    for (int i = 0; i < message.length(); i += 2) {
        char a = message[i];
        char b = message[i + 1];

        pair<int, int> pos1 = findPosition(matrix, a);
        int row1 = pos1.first, col1 = pos1.second;
        pair<int, int> pos2 = findPosition(matrix, b);
        int row2 = pos2.first, col2 = pos2.second;

        cout << "Decrypting pair: " << a << b << " -> Positions: (" << row1 << "," << col1 << ") and (" << row2 << "," << col2 << ")\n";

        if (row1 == row2) {
            result += matrix[row1][(col1 - 1 + 5) % 5];
            result += matrix[row2][(col2 - 1 + 5) % 5];
        } else if (col1 == col2) {
            result += matrix[(row1 - 1 + 5) % 5][col1];
            result += matrix[(row2 - 1 + 5) % 5][col2];
        } else {
            result += matrix[row1][col2];
            result += matrix[row2][col1];
        }

        cout << "Decrypted pair: " << result[result.length() - 2] << result[result.length() - 1] << "\n";
    }
    return result;
}

int main() {
    string key = "ketan";
    string message = "meetmeatthebridge";

    vector<vector<char>> matrix = createMatrix(key);

    string encrypted = playfairEncrypt(message, matrix);
    cout << "Encrypted: " << encrypted << endl;

    string decrypted = playfairDecrypt(encrypted, matrix);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}