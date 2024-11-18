// Write a program to implement the Chinese Remainder Theorem.

#include <bits/stdc++.h>
using namespace std;

long long MI_using_EEA(long long a, long long b)
{
    // here, a is our n from Zn. and b is the number we want to find MI for.
    long long r1 = a, r2 = b;
    long long s1 = 1, s2 = 0;
    long long t1 = 0, t2 = 1;

    while (r2 != 0)
    {
        long long q = r1 / r2;
        r1 = r1 - q * r2;
        swap(r1, r2);
        s1 = s1 - q * s2;
        swap(s1, s2);
        t1 = t1 - q * t2;
        swap(t1, t2);
    }
    if (t1 < 0)
        t1 += a;

    return t1;
}

int main()
{
    long long n;
    cout << "Enter the number of equations: ";
    cin >> n;

    // intake of equations.
    vector<long long> a(n), m(n);
    for (long long i = 0; i < n; i++)
    {
        cout << "Enter coefficient " << i + 1 << ": ";
        cin >> a[i];
    }

    for (long long i = 0; i < n; i++)
    {
        cout << "Enter modulus " << i+1 << ": ";
        cin >> m[i];
    }

    // evaluating M.
    long long M = 1;
    for (long long i = 0; i < n; i++)
    {
        M *= m[i];
    }

    long long ans = 0;
    for (long long i = 0; i < n; i++)
    {
        long long Mi = M / m[i];
        ans += a[i] * Mi * MI_using_EEA(m[i], Mi);
    }

    cout << "The solution is: " << ans % M << "\n";

    return 0;
}