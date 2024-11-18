// Q1. Write a program to list all Zn which is a field under addition and multiplication in the range of 2 to 100.

#include <bits/stdc++.h>
using namespace std;

bool isGroup(vector<int> zn, int n)
{
    // closure
    for (int i = 0; i < zn.size(); i++)
    {
        for (int j = 0; j < zn.size(); j++)
        {
            if ((zn[i] + zn[j]) % n >= n || (zn[i] + zn[j]) % n < 0)
            {
                return false;
            }
        }
    }

    // associativity
    for (int i = 0; i < zn.size(); i++)
    {
        for (int j = 0; j < zn.size(); j++)
        {
            for (int k = 0; k < zn.size(); k++)
            {
                if (((zn[i] + zn[j]) % n + zn[k]) % n != (zn[i] + (zn[j] + zn[k]) % n) % n)
                {
                    return false;
                }
            }
        }
    }

    // identity element
    bool hasIdentity = false;
    for (int i = 0; i < zn.size(); i++)
    {
        bool isIdentity = true;
        for (int j = 0; j < zn.size(); j++)
        {
            if ((zn[i] + zn[j]) % n != zn[j])
            {
                isIdentity = false;
                break;
            }
        }
        if (isIdentity)
        {
            hasIdentity = true;
            break;
        }
    }
    if (!hasIdentity)
    {
        return false;
    }

    // inverse elements
    for (int i = 0; i < zn.size(); i++)
    {
        bool hasInverse = false;
        for (int j = 0; j < zn.size(); j++)
        {
            if ((zn[i] + zn[j]) % n == 0)
            {
                hasInverse = true;
                break;
            }
        }
        if (!hasInverse)
        {
            return false;
        }
    }
    return true;
}

bool isAbelianGroup(vector<int> zn, int n)
{
    // Check if it's a group first
    if (!isGroup(zn, n))
    {
        return false;
    }

    // Check for commutativity
    for (int i = 0; i < zn.size(); i++)
    {
        for (int j = 0; j < zn.size(); j++)
        {
            if ((zn[i] + zn[j]) % n != (zn[j] + zn[i]) % n)
            {
                return false;
            }
        }
    }
    return true;
}

bool isCyclicGroup(vector<int> zn, int n){
    for (int i = 0; i < zn.size(); i++)
    {
        vector<bool> generated(n, false);
        int element = zn[i];
        for (int j = 0; j < n; j++)
        {
            int result = (element * j) % n;
            if (find(zn.begin(), zn.end(), result) != zn.end())
            {
                generated[result] = true;
            }
        }
        if (all_of(generated.begin(), generated.end(), [](bool v) { return v; }))
        {
            return true;  // Found a generator, so it's cyclic
        }
    }
    return false;  // No generator found, not cyclic
}

bool isRing(vector<int> zn, int n) {
    // Check if it's an abelian group under addition
    if (!isAbelianGroup(zn, n)) {
        return false;
    }

    // Check closure under multiplication
    for (int i = 0; i < zn.size(); i++) {
        for (int j = 0; j < zn.size(); j++) {
            int product = (zn[i] * zn[j]) % n;
            if (find(zn.begin(), zn.end(), product) == zn.end()) {
                return false;
            }
        }
    }

    // Check associativity under multiplication
    for (int i = 0; i < zn.size(); i++) {
        for (int j = 0; j < zn.size(); j++) {
            for (int k = 0; k < zn.size(); k++) {
                if (((zn[i] * zn[j]) % n * zn[k]) % n != (zn[i] * (zn[j] * zn[k]) % n) % n) {
                    return false;
                }
            }
        }
    }

    // Check distributivity
    for (int i = 0; i < zn.size(); i++) {
        for (int j = 0; j < zn.size(); j++) {
            for (int k = 0; k < zn.size(); k++) {
                if ((zn[i] * (zn[j] + zn[k]) % n) % n != ((zn[i] * zn[j]) % n + (zn[i] * zn[k]) % n) % n) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool isCommutativeRing(vector<int> zn, int n) {
    // First, check if it's a ring
    if (!isRing(zn, n)) {
        return false;
    }

    // Check commutativity under multiplication
    // (We don't need to check for addition as isAbelianGroup already ensures that)
    for (int i = 0; i < zn.size(); i++) {
        for (int j = 0; j < zn.size(); j++) {
            if ((zn[i] * zn[j]) % n != (zn[j] * zn[i]) % n) {
                return false;
            }
        }
    }

    return true;
}

bool isIntegralDomain(vector<int> zn, int n) {
    // First, check if it's a commutative ring
    if (!isCommutativeRing(zn, n)) {
        return false;
    }

    // Check for multiplicative identity
    bool hasMultiplicativeIdentity = false;
    int identity = -1;
    for (int i = 0; i < zn.size(); i++) {
        bool isIdentity = true;
        for (int j = 0; j < zn.size(); j++) {
            if ((zn[i] * zn[j]) % n != zn[j]) {
                isIdentity = false;
                break;
            }
        }
        if (isIdentity) {
            hasMultiplicativeIdentity = true;
            identity = zn[i];
            break;
        }
    }

    if (!hasMultiplicativeIdentity) {
        return false;
    }

    // Check for zero divisors
    for (int i = 0; i < zn.size(); i++) {
        if (zn[i] == 0) continue; // Skip zero
        for (int j = 0; j < zn.size(); j++) {
            if (zn[j] == 0) continue; // Skip zero
            if ((zn[i] * zn[j]) % n == 0) {
                return false; // Found a zero divisor
            }
        }
    }

    return true;
}

bool isField(vector<int> zn, int n) {
    // First, check if it's an integral domain
    if (!isIntegralDomain(zn, n)) {
        return false;
    }

    // Find the multiplicative identity
    int identity = -1;
    for (int i = 0; i < zn.size(); i++) {
        bool isIdentity = true;
        for (int j = 0; j < zn.size(); j++) {
            if ((zn[i] * zn[j]) % n != zn[j]) {
                isIdentity = false;
                break;
            }
        }
        if (isIdentity) {
            identity = zn[i];
            break;
        }
    }

    // Check for multiplicative inverse for every non-zero element
    for (int i = 0; i < zn.size(); i++) {
        if (zn[i] == 0) continue; // Skip zero

        bool hasInverse = false;
        for (int j = 0; j < zn.size(); j++) {
            if ((zn[i] * zn[j]) % n == identity) {
                hasInverse = true;
                break;
            }
        }

        if (!hasInverse) {
            return false; // Found an element without a multiplicative inverse
        }
    }

    return true;
}

int main()
{
    for (int n = 2; n <= 100; n++) {
        vector<int> zn;
        for (int i = 0; i < n; i++) {
            zn.push_back(i);
        }
        
        if (isField(zn, n)) {
            if (n == 2) {
                cout << "The following values of Zn are fields:" << endl;
                cout << "Z" << n;
            } else {
                cout << ", Z" << n;
            }
        }
        if (n == 100) {
            cout << endl;
        }
    }
}