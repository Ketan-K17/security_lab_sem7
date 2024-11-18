// Q2. Write a program to find the list of cyclic group present within a range (Example: 2000 to 3000).

#include <bits/stdc++.h>
using namespace std;

void toBinary(unsigned num, vector<int> &binaryVec) {
    if (num > 1)
        toBinary(num / 2, binaryVec);
    binaryVec.push_back(num % 2);
}

int modularExponentiation(int base, int exp, int mod) {
    vector<int> binaryExp;
    toBinary(exp, binaryExp);
    reverse(binaryExp.begin(), binaryExp.end());

    int result = (binaryExp[0] == 1) ? base : 1;
    int currentPower = base;

    for (int i = 1; i < binaryExp.size(); i++) {
        currentPower = (currentPower * currentPower) % mod;
        if (binaryExp[i] == 1) {
            result = (result * currentPower) % mod;
        }
    }

    return result;
}

int computeGCD(int a, int b) {
    int minVal = min(a, b);
    while (minVal > 0) {
        if (a % minVal == 0 && b % minVal == 0) {
            break;
        }
        minVal--;
    }
    return minVal;
}

bool isCyclicGroup(int num) {
    vector<int> znStar;
    for (int i = 1; i < num; i++) {
        if (computeGCD(i, num) == 1) {
            znStar.push_back(i);
        }
    }

    int phi = znStar.size();
    vector<int> divisors;
    for (int i = 1; i <= phi; i++) {
        if (phi % i == 0) {
            divisors.push_back(i);
        }
    }

    unordered_map<int, vector<int>> orderMap;
    for (int elem : znStar) {
        for (int div : divisors) {
            if (modularExponentiation(elem, div, num) == 1) {
                orderMap[div].push_back(elem);
                break;
            }
        }
    }

    return !orderMap[phi].empty();
}

int main() {
    vector<int> cyclicGroups;
    int rangeStart, rangeEnd;

    cout << "Enter the start value of the range: " << endl;
    cin >> rangeStart;
    cout << "Enter the end value of the range: " << endl;
    cin >> rangeEnd;

    for (int i = rangeStart; i <= rangeEnd; i++) {
        if (isCyclicGroup(i)) {
            cyclicGroups.push_back(i);
        }
    }

    for (int group : cyclicGroups) {
        cout << group << " ";
    }

    return 0;
}