#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define print_v(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(20, '=') << endl

#define eb emplace_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define ff first
#define ss second

typedef long long ll;

struct FlowEdge {
    int v, u;
    int cap, flow = 0;
    FlowEdge(int v, int u, int cap) : v(v), u(u), cap(cap) {}
};

const int N = 500 + 5;
const int INF = 1e9 + 5;

int V,E,s,t;
int ptr[N];
int level[N];

queue<int> Q;
vector<int> G[N]; // 0-indexed
vector<FlowEdge> edges; 

void add_edge(int v, int u, ll cap) {
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
            Q.push(edges[id].u);
        }
    }
    return level[t] != -1;
}

int dfs(int v, int pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int& cid = ptr[v]; cid < (int)G[v].size(); cid++) {
        int id = G[v][cid];
        int u = edges[id].u;
        if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;
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
        Q.push(s);
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    
    // Init
    V = 4; s = 0; t = 3;
    
    // Build graph
    add_edge(0,1,1);
    add_edge(1,3,1);
    add_edge(1,2,2);
    add_edge(0,2,1);
    add_edge(2,3,1);
    cout << "Max flow : " << max_flow() << endl;

    return 0;
}
