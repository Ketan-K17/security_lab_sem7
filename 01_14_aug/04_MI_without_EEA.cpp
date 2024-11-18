// Q4. Write a program to find MI of two given numbers, along with n value, without using Extended Euclidean Algorithm.

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    cout << "Enter the value of n and the number you want to find MI for : ";
    cin >> a >> b;
    for (int i = 0; i < a; i++)
    {
        if ((b * i) % a == 1)
        {
            cout << "MI = " << i << "\n";
            break;
        }
    }
    return 0;
}