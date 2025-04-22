#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int INF = 1e9;

int n,m;
int timer;
int low[N];
int tin[N];
bool vis[N];
bool cut_point[N];
vector<int> G[N];

void dfs(int u, int p = -1) {
	tin[u] = low[u] = timer++;
	vis[u] = true;
	int children = 0;
	for (int v : G[u]) {
		if (v == p) continue;
		if (vis[v]) {
			low[u] = min(low[u], tin[v]);
		} else {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (p != -1 and low[v] >= tin[u]) {
				cut_point[u] = true;
			}
			children++;
		}
	}
    if (p == -1 and children > 1) {
        cut_point[u] = true;
    }
}

int main() {
    cin >> n >> m;
	for(int i = 0; i < m; i++) {
		int u,v;
        cin >> u >> v;
        u--; v--;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(0);
	for(int i = 0; i < n; i++) {
        cout << cut_point[i] << " ";
	}
	return 0;
}
