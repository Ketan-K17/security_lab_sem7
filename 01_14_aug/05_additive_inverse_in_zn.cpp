// Q5. Write a program to find the additive inverse of a given number in Zn.

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    cout << "Enter the value of n and the number you want to find Additive Inverse for : ";
    cin >> a >> b;
    for (int i = 0; i < a; i++)
    {
        if ((b + i) % a == 0)
        {
            cout << "Additive Inverse = " << i << "\n";
            break;
        }
    }
    return 0;
}