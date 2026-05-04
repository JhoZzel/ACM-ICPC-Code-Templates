#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;

int n,m;
int color[N];
int in[N];
int out[N];
int par[N];
int dp[N];
bool is_bridge[N];
vector<pair<int,int>> G[N];

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

void pre_dfs(int u, int p = 0) {
    color[u] = 1;
    par[u] = p;
    for (auto [v, id] : G[u]) {
        if (v == p or color[v] == 2) continue;
        if (color[v]) {
            out[u] += 1;
            in[v] += 1;
        } else {
            pre_dfs(v, u);
        }
    }
    color[u] = 2;
}

void dfs(int u) {
    color[u] = 1;
    dp[u] = out[u] - in[u];
    for (auto [v, id] : G[u]) {
        if (v == par[u] or color[v] == 2) continue;
        if (color[v]) {
            // back edges
        } else {
            dfs(v);
            dp[u] += dp[v];
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
        //u--; v--;
        G[u].emplace_back(v, i);
        G[v].emplace_back(u, i);
    }

    pre_dfs(0);
    memset(color,0,sizeof(color));
    dfs(0);

    for (int i = 1; i < n; i++) {
        if (dp[i]) continue;
        for (auto [v, id] : G[i]) {
            if (v == par[i]) {
                is_bridge[id] = 1;
            }
        }
    }


    vector<pair<int,int>> edges;
    for (int i = 0; i < n; i++) {   
        if (dp[i]) continue;
        for (auto [v, id] : G[i]) {
            if (v == par[i]) {
                edges.emplace_back(min(i, v), max(i, v));
                break;
            }
        }
    }

    sort(edges.begin(), edges.end());
    for (auto [u, v] : edges) cout << u << " " << v << '\n';

    return 0;
}
