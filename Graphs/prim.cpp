#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;
typedef long long ll;
typedef tuple<int,int,int> iii;
typedef priority_queue<iii, vector<iii>, greater<iii>> pq_min;

const int N = 2e5 + 5;

int n;
int m;
bool vis[N];
vector<pair<int,int>> G[N];

int main() {
    fast_io;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        u--; v--;
        G[u].emplace_back(v,w);
        G[v].emplace_back(u,w);
    }

    pq_min Q;
    Q.emplace(0,0,-1);
    vector<pair<int,int>> T;
    ll ans = 0;
    while(!Q.empty()) {
        int u, to, w_min;
        tie(w_min, u, to) = Q.top(); Q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        T.emplace_back(u, to);
        ans += w_min;
        for (auto [v, w] : G[u]) {
            if (vis[v]) continue;
            Q.emplace(w,v,u);
        }
    }
    T.erase(T.begin());

    cout << ans << "\n";
    cout << T.size() << "\n";
    for (auto [u,v] : T) {
        cout << u + 1 << " " << v + 1 << "\n";
    }
    
    return 0;
}

