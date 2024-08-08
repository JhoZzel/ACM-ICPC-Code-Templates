#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define print_v(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(20, '=') << endl

#define eb emplace_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define ff first
#define ss second

typedef long long ll;

struct node {
    int sum, pre, suf, mx_sum;
    node() {}
    node(int x) :
        sum(x), pre(x), suf(x), mx_sum(x) {}
    node(int a, int b, int c, int d) :
        sum(a), pre(b), suf(c), mx_sum(d) {}
};

const int N = 1e5 + 5;
const int INF = 1e9 + 10;

int n;
int a[N];
node T[4 * N];

node neutral = node(0,-INF,-INF,-INF);

node f(node &L, node &R) { // merge function
    node ans;
    ans.sum = L.sum + R.sum;
    ans.pre = max(L.pre, L.sum + R.pre);
    ans.suf = max(R.suf, R.sum + L.suf);
    ans.mx_sum = max({L.mx_sum, R.mx_sum, L.suf + R.pre});
    return ans;
}

// id => Node's idx in the tree 1-indexed
// [tl, tr] => Range of the node || root: [1, n]

void build(int id, int tl, int tr) {
    if (tl == tr) { // leaf node value
        T[id] = node(a[tl]);
    }
    else {
        int tm = (tl + tr) / 2;
        build(2 * id, tl, tm);
        build(2 * id + 1, tm + 1, tr);
        T[id] = f(T[2 * id], T[2 * id + 1]);
    }
}
void update(int id, int tl, int tr, int pos, int x) {
    if (tl == tr) { // leaf node value
        T[id] = node(x);
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos > tm) update(2 * id + 1, tm + 1, tr, pos, x);
        else update(2 * id, tl, tm, pos, x);
        T[id] = f(T[2 * id], T[2 * id + 1]);
    }
}
node query(int id, int tl, int tr, int l, int r) {
    if (l > r) return neutral;
    if (l == tl and r == tr) return T[id];
    int tm = (tl + tr) / 2;
    node valL = query(2 * id, tl, tm, l, min(r, tm));
    node valR = query(2 * id + 1, tm + 1, tr, max(l, tm + 1), r);
    return f(valL, valR);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1,1,n);
    int q; cin >> q;
    while(q--) {
        int op; cin >> op;
        if (op == 0) {
            int i,x;
            cin >> i >> x;
            update(1,1,n,i,x);
        }
        else {
            int l,r;
            cin >> l >> r;
            cout << query(1,1,n,l,r).mx_sum << '\n';
        }
    }
    return 0;
}
