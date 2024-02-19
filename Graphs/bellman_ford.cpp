#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;

const int INF = 1e9 + 5;
const int N = 1e3 + 5;

int n,m;
int d[N];
vector<tuple<int,int,int>> edges;

bool bellman_ford(int s0) {
    fill(d, d + n, INF);
    d[s0] = 0;
    for (int i = 0; i < n; i++) {
        for (auto [u, v, w] : edges) {
            if (d[u] == INF) continue;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
            }
        }
    }
    for (auto [u, v, w] : edges) {
        if (d[u] == INF) continue;
        if (d[u] + w < d[v]) {
            return false;
        }
    }
    return true;
}

int main() {
    fast_io;
    int s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        edges.emplace_back(u,v,w);
    }
    if (not bellman_ford(s)) {
        cout << "NEGATIVE CYCLE\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (d[i] < INF) cout << d[i] << "\n";
        else cout << "INF\n";
    }
    return 0;
}

