// Bridges
// 

const int N = 1e5 + 5;

int n;
int m; 
int nc;
int timer;
int C[N];
int tin[N];
int low[N];
int deg[N];
bool vis[N];
bool bridge[N];
vector<pair<int,int>> G[N];
vector<int> GG[N];

void dfs(int u, int par = -1) {
    vis[u] = true;
    low[u] = tin[u] = timer++;
    for (auto [w, e] : G[u]) {
        if (w == par) continue;
        if (vis[w]) low[u] = min(low[u], tin[w]);
        else {
            dfs(w,u);
            low[u] = min(low[u], low[w]);
            if (low[w] > tin[u]) {
                bridge[e] = true;
            }
        }
    }
}

void solve() {
    dfs(0);
    fill(vis, vis + n, false);
    // We color the nodes for the same component
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        queue<int> Q;
        Q.emplace(i);
        vis[i] = true;
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            C[u] = nc;
            for (auto [w, e] : G[u]) {
                if (bridge[e]) continue;
                if (vis[w]) continue;
                Q.push(w);
                vis[w] = true;
            }
        }
        nc++;
    } 
    
    // We construct the induced graph (2-edge conected tree) 
    for (int i = 0; i < n; i++) {
        for (auto [w,e] : G[i]) {
            if (C[w] == C[i]) continue;
            GG[C[i]].push_back(C[w]);
            deg[C[w]]++;
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
