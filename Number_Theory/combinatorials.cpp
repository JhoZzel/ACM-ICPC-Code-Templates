#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << " [ " << #x << " = " << x << " ]\n";
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int add_mod(int a, int b) {
    return (a + b) % MOD;
}

int mul_mod(int a, int b) {
    return 1ll * a * b % MOD;
}

int pow_mod(int a, int e) {
    int r = 1;
    while(e) {
        if (e & 1) r = mul_mod(r, a);
        a = mul_mod(a, a);
        e >>= 1;
    }
    return r;
}

int inv_mod(int a) {
    return pow_mod(a, MOD - 2);
}

int fact[N];
int inv[N];

void get_fact() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = mul_mod(i, fact[i - 1]);
    }
    inv[N - 1] = pow_mod(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) {
        inv[i] = mul_mod(inv[i + 1], i + 1);
    }
}

int C(int n, int k) {
    return 1ll * fact[n] * inv[k] % MOD * inv[n - k] % MOD;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

int main() {
    fast_io;
    get_fact();
    int t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
