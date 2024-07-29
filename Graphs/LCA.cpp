#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define print_v(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(15, '=') << endl

#define eb emplace_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define ff first
#define ss second

const int N = 2e5 + 5;
const int LOG = 20;

int n;
int timer;
int tin[N];
int tout[N];
int dis[N];
int up[N][LOG];
vector<int> G[N];

void dfs(int u, int p = 0) {
    tin[u] = timer++;

    up[u][0] = p;
    for(int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    
    for(int v : G[u]) {
        if (v == p) continue;
        dis[v] = 1 + dis[u];
        dfs(v, u);
    }

    tout[u] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] and tout[v] <= tout[u];
}

int lca(int u, int v) {
    if(is_ancestor(u, v)) return u;
    if(is_ancestor(v, u)) return v;
    for(int i = LOG - 1; i >= 0; i--) {
        if(!is_ancestor(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u,v; 
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs(0);
    int q; cin >> q;
    while(q--) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        cout << lca(u,v) + 1 << '\n';
    }
    return 0;
}
