#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << " [ " << #x << " = " << x << " ]\n";
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

ll add_mod(ll a, ll b) {
    a %= MOD; b %= MOD;
    return (a + b) % MOD;
}

ll mul_mod(ll a, ll b) {
    return a % MOD * b % MOD;
}

ll pow_mod(ll a, ll e) {
    a %= MOD;
    ll r = 1;
    while(e) {
        if (e & 1) r = mul_mod(r, a);
        a = mul_mod(a, a);
        e >>= 1;
    }
    return r;
}

ll inv_mod(ll a) {
    return pow_mod(a, MOD - 2);
}

ll fact[N];
ll inv[N];

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

ll C(ll n, ll k) {
    return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
}

int main() {
    fast_io;
    get_fact();
    


    return 0;
}
