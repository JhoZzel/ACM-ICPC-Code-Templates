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

const int MOD = 1e9 + 9;

int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return (1ll * a * b) % MOD; }
int bpow(int a, int e) {
    int res = 1;
    while(e) {
        if (e & 1) res = mul(res, a);
        a = mul(a, a);
        e >>= 1;
    }
    return res;
}

const int N = 2e5 + 5;
const int E = 26;

int pot[N];
int ipot[N];
const int p = (int)uniform_int_distribution<ll>(E + 1, MOD - 1)(rng);

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
    int n;
    int h[2][N];
    
    Hash() {}
    
    void build(string &s) { // Initialize powers of 'p'
        n = s.size();
        for (int i = 0; i < n; i++) {
            h[0][i + 1] = add(h[0][i], mul(s[i] - 'a' + 1, pot[i]));
        }
        for (int i = n - 1; i >= 0; i--) {
            h[1][n - i] = add(h[1][n - 1 - i], mul(s[i] - 'a' + 1, pot[n - 1 - i]));
        }
    }

    int query(int i, int j) { // O(1)  1-indexed
        int hs = (h[0][j] - h[0][i - 1] + MOD) % MOD;
        hs = mul(hs, ipot[i - 1]);
        return hs;
    }

    bool is_palindrome(int l, int r) { // O(1)  1-indexed
        int l1 = l, l2 = (l + r) / 2;
        int hash1 = (h[0][l2] - h[0][l1 - 1] + MOD) % MOD;
        hash1 = mul(hash1, ipot[l1 - 1]);
        int r1 = (l + r + 1) / 2, r2 = r;
        int hash2 = (h[1][n + 1 - r1] - h[1][n + 1 - r2 - 1] + MOD) % MOD;
        hash2 = mul(hash2, ipot[n + 1 - r2 - 1]);
        return hash1 == hash2;
    }
} hs;

int get_hash(string &s) {
    int hash = 0;
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
        cout << "is_palindrome() : " << (hs.is_palindrome(l,r) ? "YES" : "NO") << '\n';
    }
    return 0;
}
