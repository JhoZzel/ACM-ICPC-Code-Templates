#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct FenwickTree { // 0-indexed [0, N - 1]
	int N;
	vector<ll> FT;
	FenwickTree() {}
	FenwickTree(int n) : N(n), FT(N + 1, 0) {}
	void update(int i, ll x) {
		for (++i; i <= N; i += i & -i) FT[i] += x;
	}
	ll sum(int i) { 
		i = min(i, N - 1); // out of range
		ll sa = 0;
		for (++i; i > 0; i -= i & -i) sa += FT[i];
		return sa;
	}
};

const int N = 1e5 + 5;
const int LOG = 20;

int n,q;
int a[N], h[N];
int timer, tin[N], tout[N];
int up[N][LOG];

bool block[N];
int sz[N], pi[N];
FenwickTree cnt[N], cnt_p[N];
vector<int> G[N];

void pre_dfs(int u, int p) {
	tin[u] = timer++;
	up[u][0] = p;
	for (int j = 1; j < LOG; j++) {
		up[u][j] = up[up[u][j - 1]][j - 1];
	}
	for (int v : G[u]) if (v != p) {
		h[v] = h[u] + 1;
		pre_dfs(v, u);
	}
	tout[u] = timer++;
}

bool is_ancestor(int u, int v) {
	return tin[u] <= tin[v] and tout[u] >= tout[v];
}

int lca(int u, int v) {
	if (is_ancestor(u, v)) return u;
	if (is_ancestor(v, u)) return v;
	for (int j = LOG - 1; j >= 0; j--) {
		if (!is_ancestor(up[u][j], v)) u = up[u][j];
	}
	return up[u][0];
}

int dis(int u, int v) {
	int w = lca(u, v);
	return h[u] + h[v] - 2 * h[w];
}

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

void dfs(int u, int p, vector<int> &comp, FenwickTree &ft, int H) { 
	comp.push_back(u);
	ft.update(H, a[u]);
	for (int v : G[u]) if (v != p and !block[v]) {
		dfs(v, u, comp, ft, H + 1);	
	}
}

void decompose(int x, int p, int m) {
	int cen = centroid(x, -1, m);
	vector<int> comp;
	cnt[cen] = FenwickTree(m); 
	dfs(cen, -1, comp, cnt[cen], 0);
	if (p != -1) {
		int mx = -1;
		for (int u : comp) mx = max(mx, dis(u, p));
		cnt_p[cen] = FenwickTree(mx + 1);
		for (int u : comp) cnt_p[cen].update(dis(u, p), a[u]);
	}

	if (~pi[cen]) sz[pi[cen]] = m - sz[cen]; // padre en el dfs normal
	pi[cen] = p; // padre en el centroid TREE
	block[cen] = 1;
	for (int v : G[cen]) if (!block[v]) {
		decompose(v, cen, sz[v]);
	}
}

ll query(int u, int k) {
	int v = u;
	int u_down = -1; // de donde subio el chamo
	ll ans = 0;
	while(v != -1) {
		int D = dis(u, v);
		ans += cnt[v].sum(k - D);
		if (u_down != -1) ans -= cnt_p[u_down].sum(k - D);
		u_down = v;
		v = pi[v];
	}
	return ans;
}

void update(int u, int x) {
	int v = u;
	int delta = x - a[u];
	while(v != -1) {
		cnt[v].update(dis(u, v), delta);
		if (pi[v] != -1) cnt_p[v].update(dis(u, pi[v]), delta);
		v = pi[v];
	}
	a[u] = x;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n >> q;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u,v;
		cin >> u >> v;
		u--; v--;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}

	pre_dfs(0, 0);

	decompose(0, -1, n);
	
	ll last = 0;
	while(q--) {
		int op; cin >> op;
		if (op == 0) {
			ll u,k;
			cin >> u >> k;
			u ^= last;
			k ^= last;
			u--;
			last = query(u, k);
			cout << last << "\n";
		} else {
			ll u,x;
			cin >> u >> x;
			u ^= last;
			x ^= last;
			u--;
			update(u, x);
		}
	}

	return 0;
}

// https://www.luogu.com.cn/problem/P6329
// O(qlog^2n)
// 1. Actualización puntual del peso de un nodo.
// 2. Suma de pesos de todos los nodos a distancia <= K desde u

