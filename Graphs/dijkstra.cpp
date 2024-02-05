#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;
typedef pair<int,int> ii;

const int INF = 1e9 + 5;
const int N = 1e5 + 5;

int n,m;
int D[N];
vector<ii> G[N];

void dijkstra(int s) {
    for (int i = 0; i < n; i++) D[i] = INF;
    D[s] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> Q;
    Q.emplace(0,s);
    while(!Q.empty()) {
        int u,d;
        tie(d,u) = Q.top(); Q.pop();
        if (d != D[u]) continue;
        for (auto [v, w] : G[u]) {
            if (D[u] + w < D[v]) {
                D[v] = D[u] + w;
                Q.emplace(D[v], v);
            }
        }
    }
}

int main() {
    fast_io;
    int s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        G[u].emplace_back(v,w);
    }
 
    dijkstra(s);

    for (int i = 0; i < n; i++) {
        if (D[i] == INF) cout << "INF\n";
        else cout << D[i] << "\n";
    }

    return 0;
}

