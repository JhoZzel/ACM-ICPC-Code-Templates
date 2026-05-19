#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;

const int N = 3e5 + 5;
const int LOG = 20;

int n,m;
int a[N];
int h[N];
int dis[N];
ll sum[N];
ll ans[N];
int up[N][LOG];
map<pair<int,int>, int> id;
vector<int> G[N];
vector<int> go[N], bck[N], T[N];

int lca(int u, int v) { 
    if (h[u] < h[v]) swap(u, v);
    if (h[u] != h[v]) {
        int L = h[u] - h[v];
        for (int j = 0; j < LOG; j++) {
            if ((L >> j) & 1) u = up[u][j];
        }
    }   

    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
} 

void dfs(int u) {
    sum[u] = a[u];
    for (int v : T[u]) {
        dfs(v);
        sum[u] += sum[v];
    }
}

void build_dag_bfs() {
    queue<int> Q;
    dis[0] = 0;
    Q.push(0);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : G[u]) {
            if (dis[v] == -1 or dis[v] == dis[u] + 1) {
                if (dis[v] == -1) Q.emplace(v);
                dis[v] = dis[u] + 1;
                go[u].emplace_back(v);
                bck[v].emplace_back(u);
            }
        }
    }
}

void build_dominator_tree() {
    queue<int> Q;
    vector<bool> vis(n);
    Q.emplace(0);
    vis[0] = 1;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        if (u) {
            int p = bck[u][0];
            for (int i = 1; i < sz(bck[u]); i++) {
                p = lca(p, bck[u][i]);   
            }
            h[u] = h[p] + 1;
            up[u][0] = p;
            for (int j = 1; j < LOG; j++) {
                up[u][j] = up[up[u][j - 1]][j - 1];
            }
            T[p].emplace_back(u);
        }
        for (int v : go[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                Q.emplace(v);
            }
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    memset(dis,-1,sizeof(dis));

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i< m ; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
        id[{u, v}] = id[{v, u}] = i;
    }

    // build DAG bfs
    build_dag_bfs();
    build_dominator_tree();
    dfs(0);
    
    for (int i = 0; i < n; i++) {
        if (sz(bck[i]) == 1) {
            int j = bck[i][0];
            int idx = id[{i, j}];
            ans[idx] = sum[i];
        }
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

