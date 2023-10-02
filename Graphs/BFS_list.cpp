#include <bits/stdc++.h>
#define pb push_back 
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

vvi get_adj_list(int n, int m) {
    vvi ady(n + 1);
    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        ady[u].pb(v);
        // ady[v].pb(u);
    }
    return ady;
}

void BFS(int s0, vvi &ady, int n) {
    vi level(n,-1), par(n,-1);
    queue<int> q;

    level[s0] = 0;
    q.push(0);

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : ady[u]) {
            if (level[v] != -1) continue;
            level[v] = level[u] + 1;
            par[v] = u;
            q.push(v);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i << "\t" << level[i] << "\t" << par[i] << "\n";
    }

}

int main() {
    int n,m; 
    cin >> n >> m;
    vvi ady = get_adj_list(n,m);
    BFS(0,ady,n);
    return 0;
}
