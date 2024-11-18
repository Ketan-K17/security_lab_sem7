// Write a program to find Euler totient value in Zn.

#include <bits/stdc++.h>
using namespace std; 

long long gcd(long long a, long long b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b % a, a); 
} 

long long phi(long long n) 
{ 
    long long result = 1; 
    for (long long i = 2; i < n; i++) 
        if (gcd(i, n) == 1) 
            result++; 
    return result; 
} 

int main() 
{ 
    long long n; 
    cout << "Enter the number: ";
    cin >> n;
    cout << "phi("<<n<<") = " << phi(n) << "\n"; 
    return 0; 
} 

