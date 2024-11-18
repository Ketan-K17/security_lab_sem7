// 2. Write a program to encrypt and decrypt text using affine cipher.

#include <bits/stdc++.h>

using namespace std;

class AffineCipher
{
private:
    int a, b;
    const int m = 26; 

    int modInverse(int a, int m)
    {
        for (int x = 1; x < m; x++)
            if (((a % m) * (x % m)) % m == 1)
                return x;
        return -1;
    }

    int charToInt(char c)
    {
        return c - 'A';
    }

    char intToChar(int i)
    {
        return static_cast<char>(i + 'A');
    }

public:
    AffineCipher(int a, int b) : a(a), b(b)
    {
        cout << "Affine Cipher initialized with a=" << a << ", b=" << b << endl;
    }

    string encrypt(const string &plaintext)
    {
        cout << "Encrypting: " << plaintext << endl;
        string ciphertext;
        for (char c : plaintext)
        {
            if (isalpha(c))
            {
                int x = charToInt(toupper(c));
                int encrypted = (a * x + b) % m;
                char encryptedChar = intToChar(encrypted);
                ciphertext += encryptedChar;
                cout << "  " << c << " -> " << encryptedChar << " (x=" << x << ", E(x)=" << encrypted << ")" << endl;
            }
        }
        return ciphertext;
    }

    string decrypt(const string &ciphertext)
    {
        cout << "Decrypting: " << ciphertext << endl;
        string plaintext;
        int a_inv = modInverse(a, m);
        cout << "  Modular inverse of a: " << a_inv << endl;
        for (char c : ciphertext)
        {
            if (isalpha(c))
            {
                int y = charToInt(toupper(c));
                int decrypted = (a_inv * (y - b + m)) % m;
                char decryptedChar = intToChar(decrypted);
                plaintext += decryptedChar;
                cout << "  " << c << " -> " << decryptedChar << " (y=" << y << ", D(y)=" << decrypted << ")" << endl;
            }
        }
        return plaintext;
    }
};

string removeSpaces(const string &str)
{
    string result = str;
    result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
    cout << "Removed spaces: " << result << endl;
    return result;
}

int main()
{
    int a, b;
    string input;

    cout << "Enter the value of 'a' (must be coprime with 26): ";
    cin >> a;
    cout << "Enter the value of 'b': ";
    cin >> b;

    AffineCipher cipher(a, b);

    cin.ignore(); 

    cout << "Enter the plaintext: ";
    getline(cin, input);

    cout << "Original input: " << input << endl;

    input = removeSpaces(input);
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    cout << "Processed input: " << input << endl;

    string encrypted = cipher.encrypt(input);
    cout << "Encrypted result: " << encrypted << endl;

    string decrypted = cipher.decrypt(encrypted);
    cout << "Decrypted result: " << decrypted << endl;

    return 0;
}