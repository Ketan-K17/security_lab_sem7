// Q3. Write a program to find MI of two given numbers, along with n value, using Extended Euclidean Algorithm.

#include <bits/stdc++.h>
using namespace std;

long long MI_using_EEA(long long a, long long b){
    // here, r1 (or a) is our n from Zn. and r2 is the number we want to find MI for.
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
    cout << "x = " << s1 << ". y = " << t1 << ".\n";
    cout << "gcd = " << a << " * " << s1 << " + " << b << " * " << t1 << " = " << a*s1 + b*t1 << "\n";
    if(t1 < 0)
        t1 += a;

    return t1;
}

int main() {
    long long a, b;
    cout << "first enter value of n, and then your desired number : ";
    cin >> a >> b;
    cout << "MI of " << b << " in Z" << a << " = " << MI_using_EEA(a, b) << "\n";
    return 0;
}