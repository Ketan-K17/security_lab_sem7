// Q1. Write a program to find elements of high order in Zn* where n is a large integer.

#include <bits/stdc++.h>
using namespace std;

// Function to compute gcd
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute (a^b) % mod
long long power(long long a, long long b, long long mod) {
    long long result = 1;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % mod;
        }
        b = b >> 1;
        a = (a * a) % mod;
    }
    return result;
}

// Function to compute Euler's totient function
long long eulerTotient(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

// Function to find prime factors of a number
vector<long long> primeFactors(long long n) {
    vector<long long> factors;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            factors.push_back(p);
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    return factors;
}

// Function to find elements of high order in Zn*
vector<long long> findHighOrderElements(long long n) {
    vector<long long> highOrderElements;
    long long phi = eulerTotient(n);
    vector<long long> factors = primeFactors(phi);

    for (long long r = 2; r < n; r++) {
        if (gcd(r, n) != 1) continue; // r must be coprime with n
        bool isHighOrder = true;
        for (long long factor : factors) {
            if (power(r, phi / factor, n) == 1) {
                isHighOrder = false;
                break;
            }
        }
        if (isHighOrder) {
            highOrderElements.push_back(r);
        }
    }
    return highOrderElements;
}

int main() {
    long long n;
    cout << "Enter a large integer n: ";
    cin >> n;

    if (n <= 1) {
        cout << "n must be greater than 1." << "\n";
        return 1;
    }

    vector<long long> highOrderElements = findHighOrderElements(n);

    cout << "Elements of high order in Z" << n << "* are: ";
    for (long long elem : highOrderElements) {
        cout << elem << " ";
    }
    cout << "\n";

    return 0;
}