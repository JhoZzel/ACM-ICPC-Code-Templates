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

using ll = long long;
using pii = pair<int,int>;

ostream& operator<<(ostream& os, const pii& p) {
    return os << p.ff << " " << p.ss;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll random(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

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

int pot[2][N], ipot[2][N];
const int p[2] = {(int)uniform_int_distribution<ll>(E + 1, MOD - 1)(rng),
                  (int)uniform_int_distribution<ll>(E + 1, MOD - 1)(rng)};

void init() {
    for (int id = 0; id < 2; id++) {
        pot[id][0] = 1;
        for (int i = 1; i < N; i++) {
            pot[id][i] = mul(pot[id][i - 1], p[id]);
        }
        ipot[id][N - 1] = bpow(pot[id][N - 1], MOD - 2);
        for (int i = N - 2; i >= 0; i--) {
            ipot[id][i] = mul(ipot[id][i + 1], p[id]);
        }
    } 
}

pii get_hash(string &s) {
    int hs[2] = {0, 0};
    for (int id = 0; id < 2; id++) {
        for (int i = 0; i < sz(s); i++) {
            hs[id] = add(hs[id], mul(s[i] - 'a' + 1, pot[id][i]));
        }
    }
    return {hs[0], hs[1]};
}

int main() {
    //ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);
    init();
    string s;
    while(cin >> s) {
        cout << "hash -> " << get_hash(s) << '\n';
    }
    return 0;
}
