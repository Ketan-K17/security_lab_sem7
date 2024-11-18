// Write a program to find the order of modulo in Zn.

// order of Zn

#include <bits/stdc++.h>
using namespace std;

vector<long long> calculateMI(long long n)
{
    vector<long long> mi;
    for (long long i = 1; i < n; i++)
    {
        for (long long j = 1; j < n; j++)
        {
            long long product = i * j;
            if (product % n == 1)
            {
                mi.push_back(i);
                cout << "mi value " << i << endl;
            }
        }
    }
    return mi;
}

vector<long long> calculateFactor(long long phi)
{
    vector<long long> phiFactors;
    for (long long i = 1; i <= phi; i++)
    {
        if (phi % i == 0)
        {
            phiFactors.push_back(i);
            cout << "phi factors " << i << endl;
        }
    }
    return phiFactors;
}

void calculateOrder(vector<long long> phiFactors, vector<long long> mi, long long n)
{
    long long p = mi.size();
    long long q = phiFactors.size();

    for (long long i = 0; i < p; i++)
    {
        long long a = mi[i];
        for (long long j = 0; j < q; j++)
        {
            long long t = phiFactors[j];

            long long r = t % 22;
            long long ex = t / 2 + r;
            long long v1 = (pow(a, t / 2));
            long long v2 = pow(a, ex);
            long long val = (v1 % n) * (v2 % n);

            // cout<<"val="<<val<<" "<<"t="<<t<<ends<<"a="<<a<<endl;
            if (val % n == 1)
            {
                cout << "val=" << val << endl;
                cout << "t(" << a << ")=" << t << endl;
                break;
            }
        }
    }
}

int main()
{
    long long n;
    cout << "enter n value in Zn" << endl;
    cin >> n;
    vector<long long> mi; // Zn*

    mi = calculateMI(n);
    long long phi = mi.size();
    cout << "phi=" << phi << endl;

    vector<long long> phiFactors;
    phiFactors = calculateFactor(phi);

    calculateOrder(phiFactors, mi, n);
    return 0;
}