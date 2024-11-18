// 2. Write a program to encrypt and decrypt the message "Pay more money" using trigraph Hill Cipher where key is "GYBNQKURP".

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to convert a 3x3 string key to a 3x3 integer matrix
vector<vector<int>> keyToMatrix(const string& key) {
    vector<vector<int>> keyMatrix(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            keyMatrix[i][j] = key[i * 3 + j] - 'A';
        }
    }
    return keyMatrix;
}

// Function to encrypt a message
string encrypt(const string& message, const vector<vector<int>>& keyMatrix) {
    string encrypted = "";
    for (int i = 0; i < message.length(); i += 3) {
        for (int j = 0; j < 3; j++) {
            int sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += keyMatrix[j][k] * (message[i + k] - 'A');
            }
            encrypted += (sum % 26) + 'A';
        }
    }
    return encrypted;
}

// Function to calculate the determinant of a 3x3 matrix
int determinant(const vector<vector<int>>& matrix) {
    return (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
            matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
            matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])) % 26;
}

// Function to calculate the modular multiplicative inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

// Function to calculate the adjugate matrix
vector<vector<int>> adjugate(const vector<vector<int>>& matrix) {
    vector<vector<int>> adj(3, vector<int>(3));
    adj[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) % 26;
    adj[0][1] = (-(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]) + 26) % 26;
    adj[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) % 26;
    adj[1][0] = (-(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) + 26) % 26;
    adj[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) % 26;
    adj[1][2] = (-(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]) + 26) % 26;
    adj[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) % 26;
    adj[2][1] = (-(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]) + 26) % 26;
    adj[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    return adj;
}

// Function to decrypt a message
string decrypt(const string& encrypted, const vector<vector<int>>& keyMatrix) {
    int det = determinant(keyMatrix);
    cout << "Determinant: " << det << endl;
    int detInverse = modInverse(det, 26);
    cout << "Determinant Inverse: " << detInverse << endl;
    vector<vector<int>> adj = adjugate(keyMatrix);
    
    vector<vector<int>> inverseMatrix(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverseMatrix[i][j] = (adj[i][j] * detInverse) % 26;
        }
    }
    cout << "Inverse Matrix:" << endl;
    for (const auto& row : inverseMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<vector<int>> inverseMatrixMod25(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverseMatrixMod25[i][j] = ((inverseMatrix[i][j] % 25) + 25) % 25;
        }
    }

    cout << "Inverse Matrix Mod 25:" << endl;
    for (const auto& row : inverseMatrixMod25) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    string decrypted = "";
    for (int i = 0; i < encrypted.length(); i += 3) {
        for (int j = 0; j < 3; j++) {
            int sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += inverseMatrix[j][k] * (encrypted[i + k] - 'A');
            }
            decrypted += ((sum % 26 + 26) % 26) + 'A';
        }
    }
    return decrypted;
}

int main() {
    string key = "GYBNQKURP";
    string message = "PAYMOREMONEY";
    
    cout << "Original Plaintext: " << message << endl;
    vector<vector<int>> keyMatrix = keyToMatrix(key);
    cout << "Key Matrix:" << endl;
    for (const auto& row : keyMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    string encrypted = encrypt(message, keyMatrix);
    cout << "Encrypted: " << encrypted << endl;
    
    string decrypted = decrypt(encrypted, keyMatrix);
    cout << "Decrypted: " << decrypted << endl;
    
    return 0;
}