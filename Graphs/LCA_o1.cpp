// LCA O(1)
//

int st[2 * N][LOG];
vector<int> euler;

void dfs(int u, int p, int d = 0) {
    tin[u] = euler.size();      
    h[u] = d;
    euler.push_back(u);
    for (int v : G[u]) if (v != p) {
        dfs(v, u, d + 1);
        euler.push_back(u);
    }
}

int f(int u, int v) {
    return (h[u] < h[v]) ? u : v;
}

void build() {
    const int m = euler.size();
    for (int i = 0; i < m; i++) st[i][0] = euler[i];
    for (int j = 1, d = 1; 2 * d <= m; j++, d <<= 1) {
        for (int i = 0; i + 2 * d <= m; i++) {
            st[i][j] = f(st[i][j - 1], st[i + d][j - 1]);
        }
    }
}

int query(int u, int v) {
    int l = tin[u], r = tin[v];
    if (l > r) swap(l, r);
    int k = __lg(r - l + 1);
    int d = (1 << k);
    return f(st[l][k], st[r - d + 1][k]);
}
