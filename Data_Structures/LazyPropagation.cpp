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

const int N = 1e5 + 5;

int n,q;
ll T[4 * N];
ll lazy[4 * N];

// id => Node's idx in the tree 1-indexed
// [tl, tr] => Range of the node || root: [1, n]

void push(int id, int tl, int tr) {
    T[id] += 1ll * (tr - tl + 1) * lazy[id];
    if (tl != tr) {
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
    }
    lazy[id] = 0;
}

void update(int l, int r, int x, int id = 1, int tl = 1, int tr = n) {
    if (lazy[id]) push(id, tl, tr);
    if (l > r) return;
    if (l == tl and r == tr) {
        lazy[id] += x;
        push(id, tl, tr);
        return;
    }
    int tm = (tl + tr) / 2;
    update(l, min(r, tm), x, 2 * id, tl, tm);
    update(max(l, tm + 1), r , x, 2 * id + 1, tm + 1, tr);
    T[id] = T[2 * id] + T[2 * id + 1];
}

ll query(int l, int r, int id = 1, int tl = 1, int tr = n) {
    if (lazy[id]) push(id, tl, tr);
    if (l > r) return 0ll;
    if (l == tl and r == tr) return T[id];
    int tm = (tl + tr) / 2;
    ll valL = query(l, min(r, tm), 2 * id, tl, tm);
    ll valR = query(max(l, tm + 1), r , 2 * id + 1, tm + 1, tr);
    return valL + valR;
}

void clean(int id = 1, int tl = 1, int tr = n) {
    T[id] = lazy[id] = 0;
    if (tl == tr) return;
    int tm = (tl + tr) / 2;
    clean(2 * id, tl, tm);
    clean(2 * id + 1, tm + 1, tr);
}

void solve() {
    cin >> n >> q;
    while(q--) {
        int op; cin >> op;
        if (op == 0) {
            int l,r,x;
            cin >> l >> r >> x;
            update(l, r, x);
        }
        else {
            int l,r;
            cin >> l >> r;
            cout << query(l, r) << '\n';
        }
    }
    clean();
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

