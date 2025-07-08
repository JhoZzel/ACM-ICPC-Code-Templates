#include <bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 5;
 
int n,m;
int deg[N];
bool used[N];
vector<int> path, edges;
vector<pair<int,int>> G[N];

void clean() {
    for (int i = 0; i < n; i++) {
        deg[i] = 0;
        G[i].clear();
    }
    fill(used, used + m, 0);
    path.clear();
    edges.clear();
}

void dfs(int u) { // Hierholzer
    while(!G[u].empty()) {
        auto [v, id] = G[u].back();
        G[u].pop_back();
        if (used[id]) continue;
        used[id] = 1;
        dfs(v);
        edges.emplace_back(id);
    }
    path.push_back(u);
}

void solve() {
    int cnt_odd = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] & 1) cnt_odd += 1;
    }
    
    if (cnt_odd > 2) return;

    int st = 0;
    if (cnt_odd == 0) {
        for (int i = 0; i < n; i++) {
            if (deg[i]) st = i;
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (deg[i] & 1) st = i;
        }
    }

    dfs(st);

    if ((int)path.size() != m + 1) path.clear();
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u,v;
            cin >> u >> v;
            G[u].emplace_back(v, i);
            G[v].emplace_back(u, i);
            deg[u]++; 
            deg[v]++; 
        }
        
        solve();
        
        if (path.empty()) cout << "No\n";
        else {
            cout << "Yes\n";
            for (int u : path) cout << u << ' ';
            cout << '\n';
            for (int i : edges) cout << i << ' ';
            cout << '\n';
        }

        clean();
    }
    
    return 0;
}

// https://judge.yosupo.jp/submission/298021
