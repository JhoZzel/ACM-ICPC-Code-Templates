#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
const int N = 2e5 + 5;

struct line {
    int m;
    ll b;
    line() : m(1), b(0) {}
    line(int m, ll b) : m(m), b(b) {}
    line operator + (line other) {
        line q;
        q.m = m * other.m;
        q.b = b * other.m + other.b;
        return q;
    }
};

int n,q;
int a[N];
ll T[4 * N];
bool marked[4 * N];
line lazy[4 * N];
 
void build(int id = 1, int tl = 1, int tr = n) {
    if (tl == tr) T[id] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(2 * id, tl, tm);
        build(2 * id + 1, tm + 1, tr);
        T[id] = T[2 * id] + T[2 * id + 1];
    }
}
 
void push(int id, int tl, int tr) {
    if (!marked[id]) return;
    T[id] = T[id] * lazy[id].m + (tr - tl + 1) * lazy[id].b;
    if (tl != tr) {
        lazy[2 * id] = lazy[2 * id] + lazy[id];
        lazy[2 * id + 1] = lazy[2 * id + 1] + lazy[id];
        marked[2 * id] = marked[2 * id + 1] = 1;
    }
    lazy[id] = line();
    marked[id] = 0;
}
 
void update(int l, int r, line x, int id = 1, int tl = 1, int tr = n) {
    push(id, tl, tr);
    if (l > r) return;
    if (tl == l and tr == r) {
        lazy[id] = lazy[id] + x;
        marked[id] = 1;
        push(id, tl, tr);
    } else {
        int tm = (tl + tr) / 2;
        update(l, min(r, tm), x, 2 * id, tl, tm);
        update(max(tm + 1, l), r, x, 2 * id + 1, tm + 1, tr);
        T[id] = T[2 * id] + T[2 * id + 1];
    }
}
 
ll query(int l, int r, int id = 1, int tl = 1, int tr = n) {
    push(id, tl, tr);
    if (l > r) return 0ll;
    if (tl == l and tr == r) return T[id];
    int tm = (tl + tr) / 2;
    ll valL = query(l, min(tm, r), 2 * id, tl, tm);
    ll valR = query(max(tm + 1, l), r, 2 * id + 1, tm + 1, tr);
    return valL + valR;
}
 
int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    build();

    while(q--) {
        int op; cin >> op;
        if (op != 3) {
            int l,r,x;
            cin >> l >> r >> x;
            update(l, r, line(op == 1, x));
        } else {
            int l,r;
            cin >> l >> r;
            cout << query(l, r) << '\n';
        }
    }

    return 0;
}

// https://cses.fi/problemset/result/14825128/
