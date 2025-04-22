#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;

int n,q;
int timer;
int tin[N];
int tout[N];
int head[N];
int par[N];
int a[N];
int h[N];
int sz[N];
int T[4 * N];
int node[N];
vector<tuple<int,int,int>> edges;
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

void build(int id = 1, int tl = 0, int tr = n - 1) {
    if (tl == tr) T[id] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(2 * id, tl, tm);
        build(2 * id + 1, tm + 1, tr);
        T[id] = max(T[2 * id], T[2 * id + 1]);
    }
}
void update(int pos, int x, int id = 1, int tl = 0, int tr = n - 1) {
    if (tl == tr) T[id] = x;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(pos, x, 2 * id, tl, tm);
        else update(pos, x, 2 * id + 1, tm + 1, tr);
        T[id] = max(T[2 * id], T[2 * id + 1]);
    }
}

int query(int l, int r, int id = 1, int tl = 0, int tr = n - 1) {
    if (l > r) return 0;
    if (tl == l and tr == r) return T[id];
    int tm = (tl + tr) / 2;
    int valL = query(l, min(r, tm), 2 * id, tl, tm);
    int valR = query(max(l, tm + 1), r, 2 * id + 1, tm + 1, tr);
    return max(valL, valR);
}

int query_hld(int u, int v) { // conmutative
    if (h[u] > h[v]) swap(u, v);
    int x = head[u], y = head[v];
    if (x == y) {
        if (u == v) return 0;
        assert(tin[u] + 1 <= tin[v]);
        return query(tin[u] + 1, tin[v]);
    }
    if (h[x] < h[y]) swap(x, y), swap(u, v);
    return max(query(tin[x], tin[u]), query_hld(par[x], v));
}

void clean() {
    for (int i = 0; i < n; i++) {
        G[i].clear();
    }
    edges.clear();
    timer = 0;
}

void solve() {
    pre_dfs(0);
    dfs(0);

    for (int i = 0; i < n - 1; i++)  {
        auto [u, v, w] = edges[i];
        if (u == par[v]) swap(u, v);
        a[tin[u]] = w;
        node[i] = u;
    } 

    build();

    string op; 
    while(cin >> op) {
        if (op == "QUERY") {
            int u,v;
            cin >> u >> v;
            u--; v--;
            cout << query_hld(u, v) << "\n";
        } else if (op == "CHANGE") {
            int i,x;
            cin >> i >> x;
            i--;
            int u = node[i];
            update(tin[u], x);
        } else {
            assert(op == "DONE");
            break;
        }
    }

    clean();
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int t; cin >> t;
    while(t--) {   
        cin >> n;
        for (int i = 1; i < n; i++) {
            int u,v,w;
            cin >> u >> v >> w;
            u--; v--;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
            edges.emplace_back(u, v, w);
        }
        solve();
    }
    
    return 0;
}
