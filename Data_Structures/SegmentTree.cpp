#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int INF = 1e9 + 10;
const int N = 1e5 + 5;

struct node {
    int sum, pre, suf, mx_sum;
    node() :
        sum(0), pre(-INF), suf(-INF), mx_sum(-INF) {}
    node(int x) : 
        sum(x), pre(x), suf(x), mx_sum(x) {}
    node(int a, int b, int c, int d) : 
        sum(a), pre(b), suf(c), mx_sum(d) {}
};

int n;
int a[N];
node T[4 * N];

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

void build(int id = 1, int tl = 1, int tr = n) {
    if (tl == tr) {
        T[id] = node(a[tl]);
    }
    else {
        int tm = (tl + tr) / 2;
        build(2 * id, tl, tm);
        build(2 * id + 1, tm + 1, tr);
        T[id] = f(T[2 * id], T[2 * id + 1]);
    }
}

void update(int pos, int x, int id = 1, int tl = 1, int tr = n) {
    if (tl == tr) { 
        T[id] = node(x);
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos > tm) update(pos, x, 2 * id + 1, tm + 1, tr);
        else update(pos, x, 2 * id, tl, tm);
        T[id] = f(T[2 * id], T[2 * id + 1]);
    }
}

node query(int l, int r, int id = 1, int tl = 1, int tr = n) {
    if (l > r) return node();
    if (l == tl and r == tr) return T[id];
    int tm = (tl + tr) / 2;
    node valL = query(l, min(r, tm), 2 * id, tl, tm);
    node valR = query(max(l, tm + 1), r , 2 * id + 1, tm + 1, tr);
    return f(valL, valR);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    int q; cin >> q;
    while(q--) {
        int op; cin >> op;
        if (op == 0) {
            int i,x;
            cin >> i >> x;
            update(i, x);
        }
        else {
            int l,r;
            cin >> l >> r;
            cout << query(l, r).mx_sum << '\n';
        }
    }
    return 0;
}
