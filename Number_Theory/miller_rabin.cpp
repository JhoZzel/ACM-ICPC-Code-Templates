#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define print_v(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(20, '=') << endl

#define eb emplace_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define ff first
#define ss second

using u64 = uint64_t;
using u128 = __uint128_t;

typedef long long ll;

u64 add(u64 a, u64 b, u64 mod) { return (u128)(a + b) % mod; }
u64 mul(u64 a, u64 b, u64 mod) { return (u128) a * b % mod; }
u64 bpow(u64 a, u64 e, u64 mod) {
    u64 r = 1;
    a %= mod;
    while (e) {
        if (e & 1) r = mul(r, a, mod);
        a = mul(a, a, mod);
        e >>= 1;
    }
    return r;
}

bool check(u64 n, u64 a, u64 d, int s) {
    u64 x = bpow(a, d, n);
    if (x == 1 or x == n - 1) return 0;
    for (int r = 1; r < s; r++) {
        x = mul(x, x, n);
        if (x == n - 1) return 0;
    }
    return 1;
};

bool miller_rabin(u64 n) { 
    if (n < 2) return 0;
    int r = 0;
    u64 d = n - 1;
    while (d % 2 == 0) d >>= 1, r++;
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return 1;
        if (check(n, a, d, r)) return 0;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    
    int t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        cout << (miller_rabin(n) ? "YES" : "NO") << '\n';
    }

    return 0;
}
