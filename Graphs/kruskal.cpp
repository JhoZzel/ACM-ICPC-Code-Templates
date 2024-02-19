#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;

const int N = 2e5 + 5;

int n;
int m;
int id[N];
vector<tuple<int,int,int>> edges;
vector<int> comp[N];

void init() {
    for (int i = 0; i < n; i++) {
        id[i] = i;
        comp[i].push_back(i);
    }
}

void join(int i, int j) {
    if (comp[j].size() < comp[i].size()) swap(i, j);
    for (int u : comp[i]) {
        comp[j].push_back(u);
        id[u] = j;
    }
    comp[i].clear();
}

int main() {
    fast_io;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        u--; v--;
        edges.emplace_back(w,u,v);
    }
    sort(edges.begin(), edges.end());
    
    init();
    
    long long ans = 0;
    vector<pair<int,int>> T;
    for (auto [w, u , v] : edges) {
        if (id[u] == id[v]) continue;
        ans += w;
        join(id[u], id[v]);
        T.emplace_back(u,v);
    }
    
    cout << ans << "\n";
    cout << T.size() << "\n";
    for (auto [u, v] : T) cout << u + 1 << " " << v + 1 << "\n";
    
    return 0;
}
