// write a c++ program to find the modular inverse of a 3x3 matrix using EEA.

#include <bits/stdc++.h>
using namespace std;

void print_matrix(long long matrix[3][3]) {
    for (long long i = 0; i < 3; i++) {
        for (long long j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

long long determinant(long long matrix[3][3]) {
    long long det = 0;
    det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
        - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
        + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    
    return det;
}

long long MI_using_EEA(long long a, long long b) {
    long long r1 = a, r2 = b;
    long long s1 = 1, s2 = 0;
    long long t1 = 0, t2 = 1;

    while (r2 != 0) {
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

void inverse_matrix(long long matrix[3][3], long long mod) {
    long long det = determinant(matrix);
    long long det_inv = MI_using_EEA(mod, (det % mod + mod) % mod);

    long long adj[3][3];
    for (long long i = 0; i < 3; i++) {
        for (long long j = 0; j < 3; j++) {
            long long minor[2][2];
            long long m = 0, n = 0;
            for (long long k = 0; k < 3; k++) {
                for (long long l = 0; l < 3; l++) {
                    if (k != i && l != j) {
                        minor[m][n++] = matrix[k][l];
                        if (n == 2) {
                            m++;
                            n = 0;
                        }
                    }
                }
            }
            adj[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * (minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0]);
        }
    }

    for (long long i = 0; i < 3; i++) {
        for (long long j = 0; j < 3; j++) {
            matrix[i][j] = ((adj[i][j] * det_inv) % mod + mod) % mod;
        }
    }
}

int main() {
    
    long long matrix[3][3];
    long long det = 0;
    cout << "Enter the elements of the 3x3 matrix:\n";
    for (long long i = 0; i < 3; i++) {
        for (long long j = 0; j < 3; j++) {
            cout << "Enter element at position [" << i+1 << "][" << j+1 << "]: ";
            cin >> matrix[i][j];
        }
    }

    long long mod;
    cout << "Enter the modulus: ";
    cin >> mod;

    inverse_matrix(matrix, mod);
    cout << "Inverse matrix is: \n";
    print_matrix(matrix);
    return 0;
}