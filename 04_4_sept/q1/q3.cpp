// Q3. Write a program to find the primitive root of GF(n) where n is a prime number of powers 1.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << "enter prime number n : ";
    int n;
    cin >> n;

    for(int i = 3; i < n; i+=2){
        for(int j = 0; j < n; j++){
            int result = 1;
            vector<bool> generated(n, false);
            for (int k = 1; k < n; k++) {
                result = (result * i) % n;
                if (!generated[result]) {
                    generated[result] = true;
                    cout << i << " ^ " << k << " = " << result << endl;
                    j++;
                }
            }
            if (j == n - 1) {
                cout << i << " is a primitive root of GF(" << n << ")" << endl;
                return 0;
            }
        }
    }

    return 0;
}