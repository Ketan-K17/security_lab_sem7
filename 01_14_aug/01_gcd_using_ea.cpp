// Q1. write a c++ program to find the gcd of two numbers using euclidean algorithm

#include <bits/stdc++.h>
using namespace std;

long long Euclidean_GCD(long long a, long long b){
    if(b == 0)
        return a;

    return Euclidean_GCD(b, a%b);
}

int main() {
    long long a, b;
    cout << "Enter 2 numbers : ";
    cin >> a >> b;
    cout << "gcd = " << Euclidean_GCD(a, b) << "\n";
    return 0;
}