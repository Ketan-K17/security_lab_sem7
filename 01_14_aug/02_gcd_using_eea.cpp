// Q2. Write a program to find gcd of 2 large integers using Extended Euclidean Algorithm.

#include <bits/stdc++.h>
using namespace std;

long long Extended_Euclidean_GCD(long long a, long long b){
    long long r1 = a, r2 = b;
    long long s1 = 1, s2 = 0;
    long long t1 = 0, t2 = 1;

    while(r2 != 0){
        long long q = r1/r2;
        r1 = r1 - q*r2;
        swap(r1, r2);
        s1 = s1 - q*s2;
        swap(s1, s2);
        t1 = t1 - q*t2;
        swap(t1, t2);
    }
    return r1;
}

int main() {
    long long a, b;
    cout << "Enter 2 numbers : ";
    cin >> a >> b;
    cout << "gcd = " << Extended_Euclidean_GCD(a, b) << "\n";
    return 0;
}