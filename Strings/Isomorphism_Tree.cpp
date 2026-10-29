// Isomorphism Tree 
// CSES Tree Isomorphism II

#include<bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll random(ll L, ll R) {
	return uniform_int_distribution<ll>(L, R)(rng);
}

const int N = 2e5 + 5;
const int MOD = 1e9 + 9;

int sz[N];
ll H[N];
vector<int> G[N];

ll dfs_hash(int u, int p, int d) {
	ll hs = 1;
	for (int v : G[u]) if (v != p) {
		hs = hs * (H[d] + dfs_hash(v, u, d + 1)) % MOD;
	}
	return hs;
}

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

vector<ll> get_hash(vector<pair<int,int>> &edges) { // labeleded [0, n - 1]
	int n = edges.size() + 1; 
	for (auto [u, v] : edges) {
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	vector<int> cent;
	find_cent(0, -1, n, cent);
	vector<ll> res;
	for (int c : cent) {
		ll hs = dfs_hash(c, -1, 0); 
		res.push_back(hs);
	}
	sort(all(res));
	for (int i = 0; i < n; i++) {
		sz[i] = 0;
		G[i].clear();
	}
	return res;
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
	vector<ll> g1 = get_hash(edges[0]);
	vector<ll> g2 = get_hash(edges[1]);
	return g1 == g2;
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
