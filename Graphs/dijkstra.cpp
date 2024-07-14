#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

const int INF = 1e9 + 5;
const int N = 1e5 + 5;

int n,m;
int par[N];
vector<ii> G[N];

vector<int> dijkstra(int s0) {
    vector<int> D(n, INF);
    D[s0] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> Q;
    Q.emplace(0,s0);
    par[s0] = -1;
    while(!Q.empty()) {
        int u,d;
        tie(d,u) = Q.top(); Q.pop();
        if (d > D[u]) continue; // be careful!!
        for (auto [v, w] : G[u]) {
            if (D[u] + w < D[v]) {
                D[v] = D[u] + w;
                par[v] = u;
                Q.emplace(D[v], v);
            }
        }
    }
    return D;
}

vector<int> build_path(int to) { // We have already called the dijkstra from s0
    vector<int> path;
    while(to != -1) {
        path.push_back(to);
        to = par[to];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    fast_io;
    int s;
    cin >> n >> m >> s;
    s--;
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        u--; v--;
        G[u].emplace_back(v,w);
        G[v].emplace_back(u,w);
    }
 
    vector<int> D = dijkstra(s);

    for (int i = 0; i < n; i++) {
        if (D[i] == INF) cout << "INF\n";
        else cout << D[i] << "\n";
    }

    for (int i = 0; i < n; i++) {
        for (int e : build_path(i)) cout << e << " ";
        cout << "\n";
    }

    return 0;
}

