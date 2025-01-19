#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e6 + 5;
const int MOD = 998244353;

int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return 1ll * a * b % MOD; }
int bpow(int a, int e) {
    int r = 1;
    while (e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}
int inv(int a) { return bpow(a, MOD - 2); }

int F[N];
int Fi[N];
int C(int n, int k) {
    if (n < 0 or k < 0 or n < k) return 0;
    return 1ll * F[n] * Fi[k] % MOD * Fi[n - k] % MOD;
}

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 

    F[0] = 1;
    for (int i = 1; i < N; i++) F[i] = mul(F[i - 1], i);
    Fi[N - 1] = inv(F[N - 1]);
    for (int i = N - 2; i >= 0; i--) Fi[i] = mul(Fi[i + 1], i + 1);

    int t; cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
