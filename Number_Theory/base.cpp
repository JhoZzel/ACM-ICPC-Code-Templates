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
const int INF = 2e9;

int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return 1ll * a * b % MOD; }
int bpow(int a, ll e) {
    int r = 1;
    while(e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}
int inv(int a) { return bpow(a, MOD - 2); }

int fact[N];
int ifact[N];

void init() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = mul(i, fact[i - 1]);
    }
    ifact[N - 1] = bpow(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
}

int C(int n, int k) {
    if (n < 0 or k < 0 or n < k) return 0;
    return 1ll * fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}


int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr); 
    
    init();
    


    return 0;
}
