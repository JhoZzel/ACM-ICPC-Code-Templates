#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
using namespace std;
typedef long long ll;

ll add_mod(ll a, ll b, int mod) {
    return (a + b) % mod;
}
 
ll mul_mod(ll a, ll b, int mod) {
	ll r = 0;
	while(b) {
		if(b & 1) r = add_mod(r, a, mod);
		a = add_mod(a, a, mod);
		b >>= 1;
	}
	return r;
}
 
ll pow_mod (ll a, ll e, int mod) {
    ll r = 1;
    a %= mod;
    while (e) {
        if (e & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return r;
}

int main() {
	ll n = 28912216785947364;
    ll e = 98718271827218121;
    int mod = 1000000007;
    cout << pow_mod(n, e, mod) << "\n";
    return 0;
}
