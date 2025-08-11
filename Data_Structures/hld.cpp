#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
struct node {
    ll sum;
    node() : sum(0) {}
    node(int x) : sum(x) {}
    node operator + (node R) {
        node L = *this;
        node q;
        q.sum = L.sum + R.sum;
        return q;
    }
};


const int N = 2e5 + 5;

int n,q;
int a[N];

int h[N];
int sz[N];
int par[N];
int head[N];

int timer;
int tin[N];
int tout[N];

node T[4 * N];
vector<int> G[N];


void pre_dfs(int u, int p = 0) {
    sz[u] = 1;
    if (p == G[u][0]) swap(G[u][0], G[u].back());
    for (int &v : G[u]) if (v != p) {
        pre_dfs(v, u);
        sz[u] += v;
        if (sz[v] > sz[G[u][0]]) {
            swap(v, G[u][0]);
        }
    }
}
 
void dfs(int u, int p = 0) {
    tin[u] = timer++;
    for (int v : G[u]) if (v != p) {
        head[v] = (v == G[u][0]) ? head[u] : v;
        h[v] = h[u] + 1;
        par[v] = u;
        dfs(v, u);
    }
    tout[u] = timer - 1;
}
 
void update(int pos, int x, int id = 1, int tl = 0, int tr = n - 1) {
    if (tl == tr) T[id] = node(x);
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) 
            update(pos, x, 2 * id, tl, tm);
        else
            update(pos, x, 2 * id + 1, tm + 1, tr);
 
        T[id] = T[2 * id] + T[2 * id + 1];
    }
}
 
node query(int l, int r, int id = 1, int tl = 0, int tr = n - 1) {
    if (l > r) return node();
    if (tl == l and tr == r) return T[id];
    int tm = (tl + tr) / 2;
    node valL = query(l, min(r, tm), 2 * id, tl, tm);
    node valR = query(max(l, tm + 1), r, 2 * id + 1, tm + 1, tr);
    return valL + valR;
}
 
node query_hld(int u, int v) { // conmutative
    if (h[u] > h[v]) swap(u, v);
    int x = head[u], y = head[v];
    if (x == y) return query(tin[u], tin[v]);
    if (h[x] < h[y]) swap(x, y), swap(u, v);
    return query(tin[x], tin[u]) + query_hld(par[x], v);
}
 
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
 
    pre_dfs(0);
    dfs(0);
    
    for (int i = 0; i < n; i++) {
        update(tin[i], a[i]);
    }
 
    while(q--) {
        int op; cin >> op;
        if (op == 1) {
            int u,x;
            cin >> u >> x;
            u--;
            update(tin[u], x);
        } else {
            int v;
            cin >> v;
            v--;
            cout << query_hld(0, v).sum << "\n"; // path (0, v)
        }
    }
 
    return 0;
}
