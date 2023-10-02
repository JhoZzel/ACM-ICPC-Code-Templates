#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define pb push_back 
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

int cnt = 0;

vvi get_adj_list(int n, int m) {
    vvi ady(n);
    for (int i = 0; i < m; i++) {
        int u,v; 
        cin >> u >> v;
        u--; v--;
        ady[u].pb(v); 
        ady[v].pb(u);
    }
    return ady;
}

/*
	Counts all possible paths from the initial node s_0 = 0, 
	to all the others
	Time Complexity: O(MX_PATHS * MAX_NEIGHBOURS)
*/

void count_paths(vvi &ady, vb &vis, int s0) {
    cnt++;
    vis[s0] = 1;
    for (int u: ady[s0]) {
        if (vis[u]) continue;
        vis[u] = 1;
        count_paths(ady, vis, u);
        vis[u] = 0;
    }
}

int main() {
    fast_io;
    int n,m; 
    cin >> n >> m;
    vvi ady = get_adj_list(n,m);
    vb vis(n,0);
    count_paths(ady, vis, 0);
    cout << cnt << "\n";
    return 0;
}


