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

typedef long long ll;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return 1ll * a * b % MOD; }
int bpow(int a, int e) {
    int r = 1;
    while(e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}
int inv(int a) { return bpow(a, MOD - 2); }

int f[N];
int fi[N];

int C(int n, int k) {
    if (n < 0 or k < 0 or n < k) return 0;
    return 1ll * f[n] * fi[k] % MOD * fi[n - k] % MOD;
}



void solve() {
       
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    f[0] = 1;
    for (int i = 1; i < N; i++) f[i] = mul(f[i - 1], i);
    fi[N - 1] = inv(f[N - 1]);
    for (int i = N - 2; i >= 0; i--) fi[i] = mul(fi[i + 1], i + 1);

    int t; cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
