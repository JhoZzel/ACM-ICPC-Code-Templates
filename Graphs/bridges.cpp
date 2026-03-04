// Bridges
// 

const int N = 2e5 + 5;

int n,m,nc;
int timer;
int C[N];
int tin[N];
int low[N];
bool vis[N];
bool bridge[N];
vector<pair<int,int>> G[N];
vector<int> GG[N];

void dfs(int u, int par = -1) {
    vis[u] = 1;
    low[u] = tin[u] = timer++;
    for (auto [v, e] : G[u]) {
        if (v == par) continue;
        if (vis[v]) low[u] = min(low[u], tin[v]);
        else {
            dfs(v,u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                bridge[e] = 1;
            }
        }
    }
}

void solve() {
    dfs(0);
    fill(vis, vis + n, 0);

    // We color the nodes for the same component
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        queue<int> Q;
        Q.emplace(i);
        vis[i] = 1;
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            C[u] = nc;
            for (auto [v, e] : G[u]) {
                if (bridge[e] or vis[v]) continue;
                vis[v] = 1;
                Q.push(v);
            }
        }
        nc++;
    } 
    
    // We construct the induced graph (2-edge conected tree) 
    for (int i = 0; i < n; i++) {
        for (auto [v, e] : G[i]) {
            if (C[v] == C[i]) continue;
            GG[C[i]].push_back(C[v]);
        }
    }
    

}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v, i);
        G[v].emplace_back(u, i);
    }
    solve();
    
    return 0;
}
