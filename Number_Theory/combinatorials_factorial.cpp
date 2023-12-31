#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int fact[N];

ll mul_mod(ll a, ll b, ll mod) {
	a %= MOD;
    b %= MOD;
    return (a * b) % mod;
}
 
ll pow_mod (ll a, ll e, ll mod) {
    ll r = 1;
    a %= mod;
    while (e) {
        if (e & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return r;
}

ll inv_mod(ll a, ll p) { 
	return pow_mod(a, p - 2, p);
}

void get_factorials() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (1ll * fact[i - 1] * i) % MOD;
    }
}

int C_mod(int n, int k) {
    return mul_mod(fact[n], inv_mod(mul_mod(fact[k], fact[n- k], MOD), MOD), MOD);
}
int main() {
    fast_io;
    get_factorials();   
    int t; cin >> t;
    while(t--) {
        int a,b; 
        cin >> a >> b;
        cout << C_mod(a, b) << "\n";
    }
    return 0;
}

