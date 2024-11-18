// Q4. Perform addition and multiplication operation on GF(16) and finds additive and multiplicative inverse of each element present in GF(16).

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Define the irreducible polynomial
const uint8_t irr_poly = 0b10011; // x^4 + x + 1

// Function to add two elements in GF(16)
uint8_t gf_add(uint8_t a, uint8_t b)
{
    return a ^ b;
}

// Function to multiply two elements in GF(16)
uint8_t gf_mul(uint8_t a, uint8_t b)
{
    uint8_t p = 0;
    while (b)
    {
        if (b & 1)
            p ^= a;
        a <<= 1;
        if (a & 0b10000)
            a ^= irr_poly;
        b >>= 1;
    }
    return p;
}

// Function to find multiplicative inverse in GF(16)
uint8_t gf_inv(uint8_t a)
{
    for (uint8_t i = 1; i < 16; i++)
    {
        if (gf_mul(a, i) == 1)
            return i;
    }
    return 0; // 0 has no multiplicative inverse
}

// Function to print a 4-bit binary representation
void print_binary(uint8_t n)
{
    for (int i = 3; i >= 0; i--)
    {
        cout << ((n >> i) & 1);
    }
}

int main()
{
    // Create addition and multiplication tables
    vector<vector<uint8_t>> add_table(16, vector<uint8_t>(16));
    vector<vector<uint8_t>> mul_table(16, vector<uint8_t>(16));

    for (uint8_t i = 0; i < 16; i++)
    {
        for (uint8_t j = 0; j < 16; j++)
        {
            add_table[i][j] = gf_add(i, j);
            mul_table[i][j] = gf_mul(i, j);
        }
    }

    // Print addition table
    cout << "Addition Table:" << endl;
    for (const auto &row : add_table)
    {
        for (uint8_t val : row)
        {
            cout << setw(2) << static_cast<int>(val) << " ";
        }
        cout << endl;
    }

    // Print multiplication table
    cout << "\nMultiplication Table:" << endl;
    for (const auto &row : mul_table)
    {
        for (uint8_t val : row)
        {
            cout << setw(2) << static_cast<int>(val) << " ";
        }
        cout << endl;
    }

    // Print additive and multiplicative inverses
    cout << "\nAdditive and Multiplicative Inverses:" << endl;
    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t add_inv = gf_add(i, i); // Additive inverse is the element itself
        uint8_t mul_inv = gf_inv(i);

        cout << "Element: ";
        print_binary(i);
        cout << ", Additive Inverse: ";
        print_binary(add_inv);
        cout << ", Multiplicative Inverse: ";
        if (mul_inv != 0 || i == 1)
        {
            print_binary(mul_inv);
        }
        else
        {
            cout << "N/A";
        }
        cout << endl;
    }

    return 0;
}