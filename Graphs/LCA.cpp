#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int LOG = 20;

int n;
int timer;
int dis[N];
int tin[N];
int tout[N];
int up[N][LOG];
vector<int> G[N];

void dfs(int u, int p = 0) {
    tin[u] = timer++;

    up[u][0] = p;
    for(int j = 1; j < LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    
    for(int v : G[u]) {
        if (v == p) continue;
        dis[v] = 1 + dis[u];
        dfs(v, u);
    }

    tout[u] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] and tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = LOG - 1; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
}

int main(){
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u,v; 
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    dfs(0);

    int q; cin >> q;
    while(q--) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        cout << lca(u,v) + 1 << '\n';
    }

    return 0;
}
