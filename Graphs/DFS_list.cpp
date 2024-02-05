#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define all(x) x.begin(), x.end()
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int N = 2e5 + 5;

vvi ady;
int n,m;
int timer = 1;
vector<int> color; // 0 blanco - 1 gris - 2 negro
vector<int> par;
vector<int> tin;
vector<int> tout;

void DFS_visit(int u) {
    color[u] = 1;
    tin[u] = timer++;
    for (int w : ady[u]) {
        if (color[w] == 2) continue;
        if (color[w] == 1) {
        
        }
        else {
            par[w] = u;
            DFS_visit(w);
        }
    }
    tout[u] = timer++;
    color[u] = 2;
}

void DFS() {
    for (int i = 0; i < n; i++) {
        if (color[i]) continue;
        DFS_visit(i);
    }
}

int main() {
    fast_io;
    cin >> n >> m;
    
    ady.resize(n, vi());
    color.resize(n, 0);
    par.resize(n, -1);
    tin.resize(n);
    tout.resize(n);

    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        ady[u].push_back(v);
    }
    DFS();
    // code
    return 0;
}

