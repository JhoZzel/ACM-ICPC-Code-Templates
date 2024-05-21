#include <bits/stdc++.h>
#define dbg(x) cerr << " [ " << #x << " = " << x << " ]\n"
#define print_v(x) cerr << #x << "[]: "; for (auto e : x) cerr << e <<" "; cerr << '\n'
#define RAYA cerr << string(15,'=')
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;
const int INF = 2e9;
const int MOD = 1e9 + 7;

int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return 1ll * a * b % MOD; }
int bpow(int a, int e) {
    int r = 1;
    while(e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}
int inv(int a) { return bpow(a, MOD - 2);}

int f[N];
int finv[N];

void init() {
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = mul(i, f[i - 1]);
    }
    finv[N - 1] = bpow(f[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) {
        finv[i] = mul(finv[i + 1], i + 1);
    }
}

int C(int n, int k) {
    if (n < 0 or k < 0 or n < k) return 0;
    return 1ll * f[n] * finv[k] % MOD * finv[n - k] % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    init();
 


    return 0;
}
