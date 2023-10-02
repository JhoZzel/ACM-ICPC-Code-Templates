#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define pb push_back 
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

vvi get_adj_matrix(int n) { 
    vvi ady(n,vi(n));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int x; cin >> x;
            ady[i][j] = x;
        }
    }
    return ady;
}

vvi get_adj_list(int n, int m) {
    vvi ady(n);
    for (int i = 0; i < m; i++) {
        int u,v; 
        cin >> u >> v;
        ady[u].pb(v); 
        // ady[v].pb(u);
    }
    return ady;
}

int main() {
    fast_io;
    int n,m; 
    cin >> n >> m;
    vvi ady_list = get_adj_list(n,m);
    for (int i = 0; i < n; i++) {
        cout << "Los vecinos del nodo " << i << " son:";
        for (int v : ady[i]) cout << " " << v;
        cout << "\n";
    }
    return 0;
}
