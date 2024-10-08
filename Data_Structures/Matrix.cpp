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
using vi = vector<int>;
using Matrix = vector<vi>;

const int MOD = 1e5;
const int pot[] = {1, 10, 100, 1000, 10000};

int add(int a, int b) { return (a + b) % MOD; }
int sub(int a, int b) { return add(a, MOD - b); }
int mul(int a, int b) { return 1ll * a * b % MOD; }

using ll = long long;
using vi = vector<int>;
using Matrix = vector<vi>;

Matrix Id(int n) {
    Matrix A(n, vi(n));
    for (int i = 0; i < n; i++) A[i][i] = 1;
    return A;
}

Matrix mul(Matrix A, Matrix B) {
    const int ra = sz(A), ca = sz(A[0]);
    const int rb = sz(B), cb = sz(B[0]);
    assert(ca == rb);
    Matrix C(ra, vi(cb));
    for (int i = 0; i < ra; ++i) {
        for (int j = 0; j < cb; ++j) {
            for (int k = 0; k < ca; ++k) {
                C[i][j] = add(C[i][j], mul(A[i][k], B[k][j]));
            }
        }
    }
    return C;
}

Matrix bpow(Matrix A, ll e) {
    Matrix R = Id(sz(A));
    while(e) {
        if (e & 1) R = mul(R, A);
        A = mul(A, A);
        e >>= 1;
    }
    return R;
}

int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);
 
    int a,b,n,k;
    cin >> a >> b >> n >> k;

    Matrix A = {{2 * a, sub(b, mul(a, a))}, {1, 0}};
    Matrix f0 = {{2 * a}, {2}};
    Matrix fn = mul(bpow(A, n - 1), f0);

    int eps = 0;
    if (n % 2 == 0 and a * a != b) eps = 1;
    if (n % 2 == 1 and a * a > b) eps = 1;
    int z = fn[0][0];
    int d = (sub(z, eps) / pot[k - 1]) % 10;
    
    cout << d << '\n';
    
    return 0;
}
