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

using ll = long long;

struct FenwickTree { // 0-indexed
    int N;
    vector<int> FT;
    FenwickTree(int n): N(n + 5), FT(n + 5) {}
    void update(int i, int x) {
        for (++i; i < N; i += i & -i) FT[i] += x;
    }
    int sum(int i) {
        int sa = 0;
        for (++i; i > 0; i -= i & -i) sa += FT[i];
        return sa;
    }
    int query(int l, int r) {
        retur sum(r) - sum(l - 1);
    }
};

void solve() {
    int n;
    cin >> n;
    FenwickTree FT(n);
    
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
