#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
#define all(x) x.begin(), x.end()
#define sz(x) ((int) x.size())
using namespace std;

const int N = 2e5 + 5;

int n;
int m;
int nc;
bool vis[N];
int in[N];
int color[N];

vector<int> order;
vector<int> component;
vector<int> G[2][N];
vector<int> GG[N];

void DFS(int id, int u) {
    vis[u] = id ^ 1;
    for (int w : G[id][u]) {
        if (vis[w] == id ^ 1) continue;
        DFS(id, w);
    }
    if (id == 0) order.push_back(u);
    else component.push_back(u);
}

void solve() {
    for (int i = 0; i < n; i++) {
        if (vis[i] == 1) continue;
        DFS(0, i);
    }
    reverse(all(order));
    nc = 0;
    vector<vector<int>> SCC;
    for (int i : order) {
        if (vis[i] == 0) continue;
        DFS(1, i);
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
    cout << "Condensed Grpah:\n";
    for (auto i = 0; i < nc; i++) {
        cout << i + 1 << " : ";
        for (int e : GG[i]) cout << e + 1 << " ";
        cout << endl;
    }
}

int main() {
    fast_io;
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
