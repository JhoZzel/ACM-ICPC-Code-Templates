#include <bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 5;
 
int n,m;
int deg[N];
bool vis[N];
vector<int> path;
vector<pair<int,int>> G[N];
 
void dfs(int u) { // Hierholzer
    while(!G[u].empty()) {
        auto [v, id] = G[u].back();
        G[u].pop_back();
        if (vis[id]) continue;
        vis[id] = 1;
        dfs(v);
    }
    path.push_back(u);
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
        deg[u]++; 
        deg[v]++; 
    }
 
    for (int i = 0; i < n; i++) {
        if (deg[i] & 1) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
 
    dfs(0);
    reverse(path.begin(), path.end());

    if ((int)path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
 
    for (int u : path) cout << u + 1 << " ";
    cout << "\n";
 
    return 0;
}
