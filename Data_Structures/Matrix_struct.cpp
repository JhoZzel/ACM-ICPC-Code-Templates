#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define pv(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(20, '=') << endl

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define eb emplace_back
#define ff first
#define ss second

using ll = long long;

const int MOD = 1e9 + 7;

struct Matrix {
    int a[2][2] = {};

    Matrix() {}

    void id() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                a[i][j] = (i == j);
            }
        }
    }

    Matrix operator+(const Matrix& B) {
        Matrix C;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                C.a[i][j] = a[i][j] + B.a[i][j];
                C.a[i][j] %= MOD;
            }
        }
        return C;
    }
    Matrix operator*(const Matrix& B) {
        Matrix C;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    C.a[i][j] += 1ll * a[i][k] * B.a[k][j] % MOD;
                    C.a[i][j] %= MOD;
                }
            }
        }
        return C;
    }
    friend Matrix bpow(Matrix A, int e) {
        Matrix R; R.id();
        while (e) {
            if (e & 1) R = R * A;
            A = A * A;
            e >>= 1;
        }
        return R;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Matrix A;
    A.a[0][0] = 1;
    A.a[0][1] = 1;
    A.a[1][0] = 1;
    A.a[1][1] = 0;
    
    const int n = 10;
    cout << "Fibonacci Numbers: ";
    for (int i = 1; i < n; i++) {
        Matrix r = bpow(A, i);
        cout << r.a[0][1] << ' ';
    }
    cout << '\n';
}
