#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
const int inf = 1e9;

int n;
int m;
int timer;
int low[N];
int tin[N];
bool vis[N];
bool cut_point[N];
vector<int> G[N];

void DFS(int u, int p = -1) {
	tin[u] = low[u] = timer++;
	vis[u] = true;
	int children = 0;
	for(int v : G[u]) {
		if(v == p) continue;
		if(vis[v]) {
			// Es una backedge, aporta a low[u]
			low[u] = min(low[u], tin[v]);
		}
		else {
			// Es una tree-edge, verificar si u es cut point
			DFS(v, u);
			// Minimizamos el low del padre con el del hijo
			low[u] = min(low[u], low[v]);
			// Ya tenemos procesado low[v]
			if(p != -1 and low[v] >= tin[u]) {
				// u es articulacion si low[v] >= tin[u] cuando u no es la raíz
				cut_point[u] = true;
			}
			children++;
		}
	}
	// Si es la raiz, es articulacion si tiene 2 o más hijos
	if(p == -1 and children > 1) cut_point[u] = true;
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	DFS(0);
	for(int i = 0; i < n; i++) {
		if(cut_point[i]) {
			printf("%d\n", i);
		}
	}
	return 0;
}
