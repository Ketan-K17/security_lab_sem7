// Q3. Write a program to find the order of an element in Zn* where n is a large integer.

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, a;
    cout << "Enter n and a: ";
    cin >> n >> a;

    long long remainder = 0;
    long long k = 1;
    long long result = a % n;
    while (result != 1) {
        result = (result * a) % n;
        k++;
    }
    cout << "Order of " << a << " mod " << n << " is " << k << "\n";

    return 0;
}