// SCC
//

const int N = 5e5 + 5;

int n,m,nc;
int c[N];
int in[N];
bool vis[N];
vector<int> GG[N];
vector<int> G[2][N];
vector<vector<int>> SCC;

void dfs(int id, int u, vector<int> &z) {
    vis[u] = 1;
    for (int v : G[id][u]) {
        if (vis[v]) continue;
        dfs(id, v, z);
    }
    z.push_back(u);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[0][u].push_back(v);
        G[1][v].push_back(u);
    }

    vector<int> order;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        dfs(0, i, order);
    }
    
    reverse(order.begin(), order.end());

    fill(vis, vis + n, 0);
    
    nc = 0;
    for (int u : order) {
        if (vis[u]) continue;
        vector<int> comp;
        dfs(1, u, comp);
        for (int v : comp) c[v] = nc;
        SCC.push_back(comp);
        nc++;
    }

    for (int i = 0; i < n; i++) {
        for (int j : G[0][i]) {
            if (c[i] == c[j]) continue;
            GG[c[i]].push_back(c[j]);
            in[c[j]]++;
        }
    }

    // debugging
    cout << "SCC:\n";
    for (auto comp : SCC) { // topological order
        for (int e : comp) cout << e + 1 << " ";
        cout << endl;
    }

    cout << "Condensed Graph:\n";
    for (auto i = 0; i < nc; i++) {
        cout << i + 1 << " : ";
        for (int e : GG[i]) cout << e + 1 << " ";
        cout << endl;
    }

    return 0;
}
