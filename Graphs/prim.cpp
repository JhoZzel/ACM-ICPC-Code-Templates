#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n,m;
bool vis[N];
vector<pair<int,int>> G[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        u--; v--;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    
    multiset<tuple<int,int,int>> ms;
    ms.emplace(0, 0, 0);
    vector<pair<int,int>> T;
    long long ans = 0;
    while(!ms.empty()) {
        auto [w_min, u, to] = *ms.begin();
        ms.erase(ms.begin());
        if (vis[u]) continue;
        vis[u] = true;
        T.emplace_back(u, to);
        ans += w_min;
        for (auto [v, w] : G[u]) {
            if (vis[v]) continue;
            ms.emplace(w, v, u);
        }
    }
    T.erase(T.begin()); 

    cout << ans << "\n";
    cout << T.size() << "\n";
    for (auto [u,v] : T) cout << u + 1 << " " << v + 1 << "\n";

    return 0;
}
