#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define pv(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(20, '=') << endl

#define eb emplace_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define ff first
#define ss second

using ll = long long;

const int INF = 1e9 + 10;
const int N = 2e5 + 5;
const int LOG = 18;

int n;
int a[N];
int jmp[N][LOG];

int f(int a, int b) {
    return min(a, b);
}

void build() { // 0-indexed
    for (int i = 0; i < n; i++) jmp[i][0] = a[i];
    for(int d = 1, p = 1; 2 * p <= n; d++, p <<= 1) {
        for(int i = 0; i + 2 * p - 1 < n; i++) {
            jmp[i][d] = f(jmp[i][d - 1], jmp[i + p][d - 1]);
        }
    }
}

int query(int l, int r) { // f(A) = f(S(A)) 
    int d = r - l + 1; 
    int k = 31 - __builtin_clz(d); 
    return f(jmp[l][k], jmp[r - (1 << k) + 1][k]);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    
    build();
    
    int q; cin >> q;
    while(q--) {
        int l,r;
        cin >> l >> r;
        l--; r--;
        cout << query(l, r) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 

    int t; cin >> t;
    while(t--) {
        solve();
    }
 
    return 0;
}
