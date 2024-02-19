#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;
typedef long long ll;

const int N = 1e3 + 5;
const int INF = 1e9;

int n;
int m;
bool vis[N];
int edge[N];
int G[N][N];

void init() {
    for (int i = 0; i < n; i++) {
        fill(G[i], G[i] + n, INF);
    }
}

void Prim(int s0) {
    for (int i = 0; i < n; i++) edge[i] = G[i][s0];
    edge[s0] = 0;
    vis[s0] = true;
    for (int i = 1; i < n; i++) {
        int v = - 1;
        for (int j = 0; j < n; j++) {
            if (vis[j]) continue;
            if (v == -1 or edge[j] < edge[v]) v = j;
        }
        vis[v] = true;
        for (int j = 0; j < n; j++) {
            if (vis[j]) continue;
            edge[j] = min(edge[j], G[j][v]);
        }
    }
}

int main() {
    fast_io;
    cin >> n >> m;
    init();
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        u--; v--;
        G[u][v] = w;
        G[v][u] = w;
    }
    Prim(0);
    cout << accumulate(edge, edge + n, 0ll);
    return 0;
}

