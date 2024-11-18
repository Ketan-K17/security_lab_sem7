// Write a program to implement modular exponentiation using repeated squaring and multiplication algorithm.

#include <bits/stdc++.h>
using namespace std;

long long Repeat_Sq_and_mult(long long A, long long k, long long mod) {
    long long b = 1;
    while (k > 0) {
        if (k % 2 == 1) {
            b = (b * A) % mod;
        }
        A = (A * A) % mod;
        k /= 2;
    }
    return b;
}

int main() {
    long long A, k, mod;
    cout << "Enter the base: ";
    cin >> A;
    cout << "Enter the exponent: ";
    cin >> k;
    cout << "Enter the modulus: ";
    cin >> mod;
    cout << A << "^" << k << " mod " << mod << " = " << Repeat_Sq_and_mult(A, k, mod) << "\n";
    return 0;
}