#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n,n,nc;
bool vis[N];
int in[N];
int color[N];

vector<int> order;
vector<int> component;
vector<int> G[2][N];
vector<int> GG[N];

void dfs(int id, int u) {
    vis[u] = id ^ 1;
    for (int w : G[id][u]) {
        if (vis[w] == (id ^ 1)) continue;
        dfs(id, w);
    }
    if (id == 0) order.push_back(u);
    else component.push_back(u);
}

void solve() {
    for (int i = 0; i < n; i++) {
        if (vis[i] == 1) continue;
        dfs(0, i);
    }
    reverse(order.begin(), order.end());
    nc = 0;
    vector<vector<int>> SCC;
    for (int i : order) {
        if (vis[i] == 0) continue;
        dfs(1, i);
        for (int u : component) color[u] = nc;
        SCC.push_back(component);
        component.clear();
        nc++;
    }

    for (int i = 0; i < n; i++) {
        for (int w : G[0][i]) {
            if (color[i] == color[w]) continue;
            GG[color[i]].push_back(color[w]);
            in[color[w]]++;
        }
    }
    // Printing
    cout << "SCC:\n";
    for (auto comp : SCC) {
        for (int e : comp) cout << e + 1 << " ";
        cout << endl;
    }
    cout << "Condensed Graph:\n";
    for (auto i = 0; i < nc; i++) {
        cout << i + 1 << " : ";
        for (int e : GG[i]) cout << e + 1 << " ";
        cout << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[0][u].push_back(v);
        G[1][v].push_back(u);
    }
    solve();
    return 0;
}
