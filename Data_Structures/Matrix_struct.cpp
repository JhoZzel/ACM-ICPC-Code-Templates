#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

struct Matrix {
    ll a[2][2];

    Matrix() {
        memset(a, 0, sizeof(a));
    }

    void id() {
        for (int i = 0; i < 2; i++) 
            for (int j = 0; j < 2; j++) 
                a[i][j] = (i == j);
    }

    ll* operator [] (int i) {
        return a[i];
    }

    Matrix operator + (Matrix &B) {
        Matrix C;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                C[i][j] = (a[i][j] + B[i][j]) % MOD;
            }
        }
        return C;
    }

    Matrix operator * (Matrix &B) {
        Matrix C;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    C[i][j] += a[i][k] * B[k][j] % MOD;
                    C[i][j] %= MOD;
                }
            }
        }
        return C;
    }
    
    friend Matrix bpow(Matrix A, ll e) {
        Matrix R; R.id();
        while (e) {
            if (e & 1) R = R * A;
            A = A * A;
            e >>= 1;
        }
        return R;
    }
};

void apply(Matrix M, ll &x, ll &y) {
    ll nx = M[0][0] * x + M[0][1] * y;
    ll ny = M[1][0] * x + M[1][1] * y;
    x = nx % MOD;
    y = ny % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Matrix A;
    A[0][0] = 1; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 0;

    ll n; cin >> n;
    ll x = 1, y = 0;
    apply(bpow(A, n), x, y);
    cout << y << "\n";

    return 0;
}

// https://cses.fi/problemset/result/13314961/
