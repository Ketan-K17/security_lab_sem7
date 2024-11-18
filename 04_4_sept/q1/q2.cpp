// Q2. Write a program to find the list of prime field and extension field in the range of 2 to 200.

#include <bits/stdc++.h>

using namespace std; 

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    vector<int> primeFields;
    vector<int> extensionFields;

    for (int i = 2; i <= 200; i++) {
        if (isPrime(i)) {
            primeFields.push_back(i);
        } else {
            // Check if it's a power of a prime
            for (int j = 2; j <= sqrt(i); j++) {
                if (isPrime(j)) {
                    int power = j;
                    while (power <= i) {
                        if (power == i) {
                            extensionFields.push_back(i);
                            break;
                        }
                        power *= j;
                    }
                    if (power == i) break;
                }
            }
        }
    }

    cout << "Prime Fields: ";
    for (int prime : primeFields) {
        cout << prime << " ";
    }
    cout << "\nExtension Fields: ";
    for (int ext : extensionFields) {
        cout << ext << " ";
    }
    return 0;
}