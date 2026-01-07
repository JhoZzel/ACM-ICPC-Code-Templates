// Bellman Ford
// 

const int INF = 1e9 + 5;
const int N = 1e3 + 5;

int n,m;
int d[N];
vector<tuple<int,int,int>> edges;

bool bellman_ford(int s0) {
    fill(d, d + n, INF);
    d[s0] = 0;
    for (int i = 0; i < n - 1; i++) {
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
