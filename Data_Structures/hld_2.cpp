// HLD f one way
//
// O(log^2 N)

using ll = long long;
 
const int N = 2e5 + 5;
const int MOD = 998244353;

struct node {
    ll a,b;
    node() : a(1), b(0) {}
    node(ll a, ll b) : a(a), b(b) {}
    node operator + (const node R) const {
        node L = *this;
        node q;
        q.a = L.a * R.a % MOD;
        q.b = (L.a * R.b + L.b) % MOD;
        return q;
    }
    int eval(int x) {
        return (a * x + b) % MOD;
    }
};

int n,q;
int timer;
int tin[N];
int tout[N];
int head[N];
int par[N];
int h[N];
int sz[N];
node val[N];
node a[N];
node T[2][4 * N];
vector<int> G[N];

void build(int id = 1, int tl = 0, int tr = n - 1) {
    if (tl == tr) T[0][id] = T[1][id] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(2 * id, tl, tm);
        build(2 * id + 1, tm + 1, tr);
        T[0][id] = T[0][2 * id] + T[0][2 * id + 1];
        T[1][id] = T[1][2 * id + 1] + T[1][2 * id];
    }
}

void update(int pos, node x, int id = 1, int tl = 0, int tr = n - 1) {
    if (tl == tr) T[0][id] = T[1][id] = x;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(pos, x, 2 * id, tl, tm);
        else update(pos, x, 2 * id + 1, tm + 1, tr);
        T[0][id] = T[0][2 * id] + T[0][2 * id + 1];
        T[1][id] = T[1][2 * id + 1] + T[1][2 * id];
    }
}
 
pair<node, node> query(int l, int r, int id = 1, int tl = 0, int tr = n - 1) { // 0-> izq-der  1-> der-izq
    if (l > r) return {node(), node()};
    if (tl == l and tr == r) return {T[0][id], T[1][id]};
    int tm = (tl + tr) / 2;
    auto [L0, L1] = query(l, min(r, tm), 2 * id, tl, tm);
    auto [R0, R1] = query(max(l, tm + 1), r, 2 * id + 1, tm + 1, tr);
    return {L0 + R0, R1 + L1};
}

void pre_dfs(int u, int p = 0) {
    sz[u] = 1;
    if (p == G[u][0]) swap(G[u][0], G[u].back());
    for (int &v : G[u]) if (v != p) {
        pre_dfs(v, u);
        sz[u] += sz[v];
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

node query_hld(int u, int v) { // non-commutative
    int x = head[u];
    int y = head[v];
    if (x == y) {
        if (h[u] < h[v]) 
            return query(tin[u], tin[v]).first;
        else 
            return query(tin[v], tin[u]).second;
    } else {
        if (h[x] > h[y]) 
            return query(tin[x], tin[u]).second + query_hld(par[x], v);
        else
            return query_hld(u, par[y]) + query(tin[y], tin[v]).first;
    }
}  

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int c,d;
        cin >> c >> d;
        val[i] = node(c, d);
    }

    for (int i = 1; i < n; i++) {
        int u,v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
 
    pre_dfs(0);
    dfs(0);
 
    for (int i = 0; i < n; i++) a[tin[i]] = val[i]; 
    build();
 
    while(q--) {
        int op; cin >> op;
        if (op == 0) {
            int u,c,d;
            cin >> u >> c >> d;
            update(tin[u], node(c, d));
        } else {
            int u,v,x;
            cin >> u >> v >> x;
            swap(u, v);// u -> v
            node q = query_hld(u, v);
            cout << q.eval(x) << "\n";
        }
    }
 
    return 0;
}
