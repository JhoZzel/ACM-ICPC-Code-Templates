#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 5;

int n,k;
ll global;
bool block[N];
int sz[N], pi[N];
vector<int> cnt;
vector<int> G[N];

int centroid(int u, int p, int m) {
	int mx = 0, cen = 0;
	sz[u] = 1;
	for (int v : G[u]) if (v != p and !block[v]) {
		cen ^= centroid(v, u, m);
		sz[u] += sz[v];
		mx = max(mx, sz[v]);
	}
	mx = max(mx, m - sz[u]);
	if (2 * mx <= m) pi[cen = u] = p;
	return cen;
}

void dfs(int u, int p, int len, bool add) { 
	if (!add) { // calculamos la rpta
		if (k - len >= 0 and k - len < (int)cnt.size()) {
			global += cnt[k - len];
		}	
	} else { // updateamos la tabla
		cnt[len] += 1;
	}
	
	for (int v : G[u]) if (v != p and !block[v]) {
		dfs(v, u, len + 1, add);	
	}
}

void decompose(int x, int p, int m) {
	int cen = centroid(x, -1, m);
	cnt.assign(m, 0); // reset all
	cnt[0] = 1;
	for (int v : G[cen]) if (!block[v]) { 
		dfs(v, cen, 1, 0); 
		dfs(v, cen, 1, 1);
	}

	if (~pi[cen]) sz[pi[cen]] = m - sz[cen];
	pi[cen] = p;
	block[cen] = 1;
	for (int v : G[cen]) if (!block[v]) {
		decompose(v, cen, sz[v]);
	}
}

// Fixed-Length Paths I CSES
// Given a tree of n nodes, your task is to count the number of distinct paths that consist of exactly k edges.

int main() { 
	cin.tie(0) -> sync_with_stdio(0);

	memset(pi,-1,sizeof(pi));

	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int u,v;
		cin >> u >> v;
		u--; v--;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}

	decompose(0, -1, n);

	cout << global << "\n";

	return 0;
}
