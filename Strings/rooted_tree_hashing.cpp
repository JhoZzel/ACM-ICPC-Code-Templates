// Rooted Tree Hashing
//

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll random(ll L, ll R) {
	return uniform_int_distribution<ll>(L, R)(rng);
}

const int N = 2e5 + 5;
const int MOD = 1e9 + 9;

ll H[N];
vector<int> G[N];

ll dfs_hash(int u, int p, int d) {
	ll hs = 1;
	for (int v : G[u]) if (v != p) {
		hs = hs * (H[d] + dfs_hash(v, u, d + 1)) % MOD;
	}
	return hs;
}

ll get_hash(vector<pair<int,int>> &edges, int root = 0) {
	int n = edges.size() + 1;
	for (auto [u, v] : edges) {
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	ll hs = dfs_hash(root, -1, 0); 
	for (int i = 0; i < n; i++) {
		G[i].clear();
	}
	return hs;
}

bool solve() {
	int n; cin >> n;
	vector<pair<int,int>> edges[2];
	for (int id : {0, 1}) {
		for (int i = 1; i < n; i++) {
			int u,v;
			cin >> u >> v;
			u--; v--;
			edges[id].emplace_back(u, v);
		}
	}
	return get_hash(edges[0]) == get_hash(edges[1]);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	for (int i = 0; i < N; i++) {
		H[i] = random(N + 1, MOD - 1);
	}

	int t; cin >> t;
	while(t--) {
		cout << (solve() ? "YES" : "NO") << "\n";
	}

	return 0;
}
