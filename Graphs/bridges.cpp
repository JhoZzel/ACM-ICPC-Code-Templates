// Bridges 
// (useful with multiedges and self loops)

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 5e5 + 5;

int n,m,nc;
int C[N];
int dp[N];
bool vis[N];
int color[N];
bool bridge[N];
vector<int> T[N];
vector<pair<int,int>> G[N];
vector<pair<int,int>> edges;

void dfs_bridge(int u, int p_id = -1) { 
    color[u] = 1;
    for (auto [v, id] : G[u]) if (id != p_id) {
        if (color[v] == 2) continue;
        if (color[v] == 1) {
            dp[u] += 1;
            dp[v] -= 1;
        } else {
            dfs_bridge(v, id);
            dp[u] += dp[v];
            if (dp[v] == 0) bridge[id] = 1;
        }
    }
    color[u] = 2;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v, i);
        G[v].emplace_back(u, i);
        edges.emplace_back(u, v);
    }

    dfs_bridge(0);

    // Paint the components C[u]
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
    for (int i = 0; i < m; i++) {
        if (!bridge[i]) continue;
        auto [u, v] = edges[i];

        u = C[u], v = C[v];

        T[u].emplace_back(v);
        T[v].emplace_back(u);
    }
    
    return 0;
}
