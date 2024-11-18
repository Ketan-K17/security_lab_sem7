// Q5. Write a program to find the square root of a modulo n where n is a large integer.

#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

vector<long long> Zn_star_generator(long long n) {
    vector<long long> Zn_star;
    for (long long i = 1; i < n; i++) {
        if (gcd(i, n) == 1) {
            Zn_star.push_back(i);
        }
    }
    return Zn_star;
}

set<long long> square_root_mod_n(long long n, long long a) {
    vector<long long> Zn_star = Zn_star_generator(n);
    set<long long> square_root;
    for (long long i = 0; i < Zn_star.size(); i++) {
        long long x = Zn_star[i];
        if(x * x % n == a) {
            square_root.insert(x);
        }
    }
    return square_root;
}

int main() {
    long long n, a;
    cout << "Enter n and a: ";
    cin >> n >> a;
    vector<long long> Znstar = Zn_star_generator(n);
    set<long long> square_root = square_root_mod_n(n, a);  
    cout << "Square Root: ";
    for(long long i : square_root) {
        cout << i << " ";
    }

    return 0;
}