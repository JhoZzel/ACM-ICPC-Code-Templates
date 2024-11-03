#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define pv(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(20, '=') << endl

#define eb emplace_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define ff first
#define ss second

using ll = long long;

const int N = 500 + 5;
const int INF = 1e9 + 9;

struct Dinic { // O(V^2 E)
    struct FlowEdge {
        int v, u;
        int cap, flow = 0;
        FlowEdge(int v, int u, int cap) : v(v), u(u), cap(cap) {}
    }; 
    
    int V,E,s,t;
    int ptr[N];
    int level[N];

    queue<int> Q;
    vector<int> G[N]; // 0-indexed
    vector<FlowEdge> edges; 

    Dinic() {}

    void init(int _V, int _s, int _t) {
        V = _V;
        s = _s;
        t = _t;
    }

    void add_edge(int v, int u, int cap = 1) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        G[v].push_back(E);
        G[u].push_back(E + 1);
        E += 2;
    }

    bool bfs() {
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int id : G[v]) {
                if (edges[id].cap - edges[id].flow < 1) continue;
                if (level[edges[id].u] != -1) continue;
                level[edges[id].u] = level[v] + 1;
                Q.emplace(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int& cid = ptr[v]; cid < sz(G[v]); cid++) {
            int id = G[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] or edges[id].cap - edges[id].flow < 1) continue;
            int tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    int max_flow() { 
        int f = 0;
        while (true) {
            fill(level, level + V, -1);
            level[s] = 0;
            Q.emplace(s);
            if (!bfs()) break;
            fill(ptr, ptr + V, 0);
            while (int pushed = dfs(s, INF)) {
                f += pushed;
            }
        }
        return f;
    }

    void clear() {
        E = 0;
        edges.clear();
        fill(G, G + V, vector<int>());
    }

} g;


void solve() {
    int n; cin >> n;
    int V = n + 62, s = 0, t = n + 61;

    g.init(V, s, t);

    for (int i = 1; i <= n; i++) {
        ll x; cin >> x;
        g.add_edge(s, i);
        for (int b = 0; b < 60; b++) {
            if ((x >> b) & 1) {
                g.add_edge(i, n + b + 1);
            }
        }
    }

    for (int b = 0; b < 60; b++) {
        g.add_edge(n + 1 + b, t); 
    }

    cout << n - g.max_flow() << '\n';

    g.clear();
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    int t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
