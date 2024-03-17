#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << "[ " << #x << " = " << x << "]\n";
using namespace std;
typedef long long ll;

const int p = 29;
const int MOD = 1e9 + 9;
const int N = 2e5 + 5;

int add_mod(int a, int b) {
    return (a + b) % MOD;
}

int mul_mod(int a, int b) {
    return (1ll * a * b) % MOD;
}

int pow_mod(int a, int e) {
    int res = 1;
    while(e) {
        if (e & 1) res = mul_mod(res, a);
        a = mul_mod(a, a);
        e >>= 1;
    }
    return res;
}

int n;
string s;

int h[2][N];
int pot[N];
int pot_inv[N];
set<int> S[N];

void init_pot() { // Initialize powers of 'p'
    pot[0] = 1;
    for (int i = 1; i < N; i++) {
        pot[i] = mul_mod(pot[i - 1], p);
    }
    pot_inv[N - 1] = pow_mod(pot[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) {
        pot_inv[i] = mul_mod(pot_inv[i + 1], p);
    }
}

void init_pre_hashes() { // just for our string 's' with length 'n' // O(n)
    for (int i = 0; i < n; i++) {
        h[0][i + 1] = add_mod(h[0][i], mul_mod(s[i] - 'a' + 1, pot[i]));
    }
    reverse(s.begin(), s.end());
    for (int i = 0; i < n; i++) {
        h[1][i + 1] = add_mod(h[1][i], mul_mod(s[i] - 'a' + 1, pot[i]));
    }
    reverse(s.begin(), s.end());
}

bool is_palindrome(int l, int r) { // O(1)
    int l1 = l, l2 = (l + r) / 2;
    int hash1 = (h[0][l2] - h[0][l1 - 1] + MOD) % MOD;
    hash1 = mul_mod(hash1, pot_inv[l1 - 1]);
    int r1 = (l + r + 1) / 2, r2 = r;
    int hash2 = (h[1][n + 1 - r1] - h[1][n + 1 - r2 - 1] + MOD) % MOD;
    hash2 = mul_mod(hash2, pot_inv[n + 1 - r2 - 1]);
    return hash1 == hash2;
}

int get_hash(string &a) { // build another hash
    int hash = 0;
    for (int i = 0; i < (int) a.size(); i++) {
        hash = add_mod(hash, mul_mod(a[i] - 'a' + 1, pot[i]));
    }
    return hash;
}

int get_hash(int i, int j) { // O(1)
    int hash = (h[0][j] - h[0][i - 1] + MOD) % MOD;
    hash = mul_mod(hash, pot_inv[i - 1]);
    return hash;
}

void solve() {
    cin >> s;
    n = s.size();
    init_pre_hashes();
    int q; cin >> q;
    while(q--) {
        int l,r;
        cin >> l >> r;
        string temp = s.substr(l - 1, r - l + 1);
        cout << " => " << temp << endl;
        cout << get_hash(l,r) << " = " << get_hash(temp) << endl;
        cout << (is_palindrome(l,r) ? "YES" : "NO") << "\n";
    }
}

int main() {
    init_pot();
    int t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
