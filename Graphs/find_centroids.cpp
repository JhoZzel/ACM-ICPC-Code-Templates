// Find centroids
// 
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 5;

int n;
int sz[N];
vector<int> G[N];

void find_cent(int u, int p, int m, vector<int>& c) {
	sz[u] = 1;
	int mx = 0;
	for (int v : G[u]) if (v != p) {
		find_cent(v, u, m, c);
		sz[u] += sz[v];
		mx = max(mx, sz[v]); 
	}
	mx = max(mx, m - sz[u]);
	if (2 * mx <= m) c.push_back(u);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n;
	for (int i = 1; i < n; i++) {
		int u,v;
		cin >> u >> v;
		u--; v--;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}

	vector<int> cent;
	find_cent(0, -1, n, cent);

	return 0;
}
