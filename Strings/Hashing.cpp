#include <bits/stdc++.h>
#define dbg(x) cerr << "[ " << #x << " = " << x << "]\n";
using namespace std;
typedef long long ll;

const int p = 311;
const int MOD = 1e9 + 9;
const int N = 2e5 + 5;

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return (1ll * a * b) % MOD;
}

int bpow(int a, int e) {
    int res = 1;
    while(e) {
        if (e & 1) res = mul(res, a);
        a = mul(a, a);
        e >>= 1;
    }
    return res;
}

int n;
string s;

int h[2][N];
int pot[N];
int pot_inv[N];

void init() { // Initialize powers of 'p'
    pot[0] = 1;
    for (int i = 1; i < N; i++) {
        pot[i] = mul(pot[i - 1], p);
    }
    pot_inv[N - 1] = bpow(pot[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) {
        pot_inv[i] = mul(pot_inv[i + 1], p);
    }
}

void init_pre_hashes() { // just for our string 's' with length 'n' // O(n)
    for (int i = 0; i < n; i++) {
        h[0][i + 1] = add(h[0][i], mul(s[i] - 'a' + 1, pot[i]));
    }
    reverse(s.begin(), s.end());
    for (int i = 0; i < n; i++) {
        h[1][i + 1] = add(h[1][i], mul(s[i] - 'a' + 1, pot[i]));
    }
    reverse(s.begin(), s.end());
}

bool is_palindrome(int l, int r) { // O(1)  1-indexed
    int l1 = l, l2 = (l + r) / 2;
    int hash1 = (h[0][l2] - h[0][l1 - 1] + MOD) % MOD;
    hash1 = mul(hash1, pot_inv[l1 - 1]);
    int r1 = (l + r + 1) / 2, r2 = r;
    int hash2 = (h[1][n + 1 - r1] - h[1][n + 1 - r2 - 1] + MOD) % MOD;
    hash2 = mul(hash2, pot_inv[n + 1 - r2 - 1]);
    return hash1 == hash2;
}

int get_hash(string &a) { // build another hash
    int hash = 0;
    for (int i = 0; i < (int) a.size(); i++) {
        hash = add(hash, mul(a[i] - 'a' + 1, pot[i]));
    }
    return hash;
}

int get_hash(int i, int j) { // O(1)  1-indexed
    int hash = (h[0][j] - h[0][i - 1] + MOD) % MOD;
    hash = mul(hash, pot_inv[i - 1]);
    return hash;
}




int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    init();
    cin >> s;
    n = s.size();
    init_pre_hashes();

    while(true) {
        int l,r;
        cin >> l >> r;
        string temp = s.substr(l - 1, r - l + 1);
        cout << " => " << temp << '\n';
        cout << get_hash(l,r) << " = " << get_hash(temp) << '\n';
        cout << "is_palindrome: ";
        cout << (is_palindrome(l,r) ? "YES" : "NO") << "\n\n";
    }
    return 0;
}
