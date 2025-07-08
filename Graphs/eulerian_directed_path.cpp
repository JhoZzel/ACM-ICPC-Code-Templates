#include <bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 5;
 
int n,m;
int in[N];
int out[N];
vector<int> path, edges;
vector<pair<int,int>> G[N];

void clean() {
    for (int i = 0; i < n; i++) {
        in[i] = out[i] = 0;
        G[i].clear();
    }
    path.clear();
    edges.clear();
}

void dfs(int u) { // Hierholzer
    while(!G[u].empty()) {
        auto [v, id] = G[u].back();
        G[u].pop_back();
        dfs(v);
        edges.emplace_back(id);
    }
    path.push_back(u);
}

void solve() {
    int start = 0, end = 0;
    for (int i = 0; i < n; i++) {
        if (out[i] == in[i] + 1) start++;
        else if (in[i] == out[i] + 1) end++;
        else if (in[i] != out[i]) return;
    }
    
    int st = 0;
    if (start == 1 and end == 1) {
        for (int i = 0; i < n; i++) if (out[i] == in[i] + 1) st = i;
    } else if (start == 0 and end == 0) {
        for (int i = 0; i < n; i++) if (out[i]) st = i;
    } else {
        for (int i = 0; i < n; i++) {
            if (in[i] != out[i]) return;
            if (in[i] and out[i]) st = i;
        }
    }
    
    dfs(st);

    if ((int)path.size() != m + 1) path.clear();

    reverse(path.begin(), path.end());
    reverse(edges.begin(), edges.end());
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
            in[v] += 1;
            out[u] += 1;
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

// https://judge.yosupo.jp/submission/298270
