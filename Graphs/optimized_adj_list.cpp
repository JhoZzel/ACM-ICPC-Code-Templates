#include <bits/stdc++.h>
#define pb push_back 
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

/*
    last[u] = Ind de la última ARISTA agregada a la lista de ady del NODO u 
    nxt[e]  = Ind de la siguiente ARISTA en la lista de ady del NODO a la cual pertenece la ARISTA e
    to[e]   = Ind del NODO hacia el cual la ARISTA de índice e se dirige 
*/

void add_edge(int u, int v, vi& last, vi& nxt, vi& to) {
    nxt.pb(last[u]);
    last[u] = to.size();
    to.pb(v);
}

void get_adj_list(int m, vi& last, vi& nxt, vi& to) {
    for (int i = 0; i < m; i++) {
        int u,v; cin >> u >> v;
        add_edge(u,v,last,nxt,to);
        // add_edge(v,u,last,nxt,to); 
    }
}

int main() {
    int n,m; 
    cin >> n >> m;
    vi last(n,-1), nxt, to;
    get_adj_list(m, last, nxt, to);
    for (int i = 0; i < n; i++) {
        cout << "Los vecinos del nodo " << i << " son:";
        for (int e = last[i]; e != -1; e = nxt[e]) {
            cout << " " << to[e];
        }
        cout << "\n";
    }
    return 0;
}
