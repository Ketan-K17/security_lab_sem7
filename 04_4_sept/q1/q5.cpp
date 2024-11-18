// Q5. Find multiplicative inverse of 95 in GF(128).

#include <bits/stdc++.h>
using namespace std;

const uint8_t FIELD_SIZE = 128;
const uint8_t IRREDUCIBLE_POLY = 0b10000011;  // x^7 + x + 1

// Function to multiply two elements in GF(128)
uint8_t gf_mul(uint8_t a, uint8_t b) {
    uint8_t result = 0;
    while (b) {
        if (b & 1)
            result ^= a;
        a <<= 1;
        if (a & 0b10000000)
            a ^= IRREDUCIBLE_POLY;
        b >>= 1;
    }
    return result;
}

// Function to find multiplicative inverse in GF(128)
uint8_t gf_inv(uint8_t a) {
    for (uint8_t i = 1; i < FIELD_SIZE; i++) {
        if (gf_mul(a, i) == 1)
            return i;
    }
    return 0;  // This should never happen for non-zero input in GF(128)
}

int main() {
    uint8_t element = 95;
    uint8_t inverse = gf_inv(element);

    cout << "Element: " << bitset<7>(element) << " (decimal " << (int)element << ")" << endl;
    cout << "Multiplicative Inverse: " << bitset<7>(inverse) << " (decimal " << (int)inverse << ")" << endl;

    // Verify the result
    uint8_t product = gf_mul(element, inverse);
    cout << "Product of element and its inverse: " << bitset<7>(product) << " (decimal " << (int)product << ")" << endl;

    return 0;
}