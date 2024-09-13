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

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

const ll MOD = 1099890859290576737;

ll add(ll a, ll b) { return (a + b) % MOD; }
ll mul(ll a, ll b) { return ((__int128_t) a * b) % MOD; }
ll bpow(ll a, ll e) {
    ll r = 1;
    while(e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}

const int N = 1e6 + 5;
const int E = 1e5 + 5;

ll pot[N], ipot[N];
const ll p = uniform_int_distribution<ll>(E + 1, MOD - 1)(rng);

void init() {
    pot[0] = 1;
    for (int i = 1; i < N; i++) {
        pot[i] = mul(pot[i - 1], p);
    }
    ipot[N - 1] = bpow(pot[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) {
        ipot[i] = mul(ipot[i + 1], p);
    }
}

struct Hash {
    ll h[N];
    Hash() {}
    void build(string &s) { // Initialize powers of 'p'
        for (int i = 0; i < sz(s); i++) {
            h[i + 1] = add(h[i], mul(s[i] - 'a' + 1, pot[i]));
        }
    }
    ll query(int i, int j) { // O(1)  1-indexed
        ll hash = (h[j] - h[i - 1] + MOD) % MOD;
        hash = mul(hash, ipot[i - 1]);
        return hash;
    }
} hs;

ll get_hash(string &s) {
    ll hash = 0;
    for (int i = 0; i < sz(s); i++) {
        hash = add(hash, mul(s[i] - 'a' + 1, pot[i]));
    }
    return hash;
}

int main() {
    //ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);
    init();
    string s; cin >> s;
    hs.build(s);
    while(true) {
        int l,r;
        cin >> l >> r;
        string temp = s.substr(l - 1, r - l + 1);
        cout << " => " << temp << '\n';
        cout << hs.query(l,r) << " = " << get_hash(temp) << '\n';
    }
    return 0;
}
