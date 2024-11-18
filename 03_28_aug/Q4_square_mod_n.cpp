// Q4. Write a program to find the quadratic residue and quadratic nonresidue mod n where n is a large integer.

#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

vector<long long> Zn_star_generator(long long n) {
    vector<long long> Zn_star;
    for (long long i = 1; i < n; i++) {
        if (gcd(i, n) == 1) {
            Zn_star.push_back(i);
        }
    }
    return Zn_star;
}

set<long long> quadratic_residue(long long n, vector<long long> Zn_star) {
    set<long long> quadratic_residue;
    for (long long i = 0; i < Zn_star.size(); i++) {
        long long a = Zn_star[i];
        long long element = (a * a) % n;
        if(find(Zn_star.begin(), Zn_star.end(), element) != Zn_star.end()) {
            quadratic_residue.insert(element);
        }
    }
    return quadratic_residue;
}

int main() {
    long long n;
    cout << "Enter the number: ";
    cin >> n;
    vector<long long> Znstar = Zn_star_generator(n);
    set<long long> quad_res = quadratic_residue(n, Znstar);  
    cout << "Quadratic Residue: ";
    for(long long i : quad_res) {
        cout << i << " ";
    }

    cout << "\nQuadratic Non-Residue: ";
    for(long long i : Znstar) {
        if(quad_res.find(i) == quad_res.end()) {
            cout << i << " ";
        }
    }

    return 0;
}