#include <bits/stdc++.h>
using namespace std;

#define x real()
#define y imag()
#define all(x) x.begin(), x.end()

using ll = long long;
using pt = complex<ll>;

struct DSU {
	vector<int> par, sz;
	DSU(int n) {
		sz.resize(n);
		par.resize(n);
		for (int i = 0; i < n; i++) {
			sz[i] = 1;
			par[i] = i;
		}
	}
	int get(int a) {
		return (a == par[a]) ? a : par[a] = get(par[a]);
	}
	bool join(int a, int b) {
		a = get(a);
		b = get(b);
		if (a == b) return 0;
		if (sz[a] < sz[b]) swap(a, b);
		par[b] = a;
		sz[a] += sz[b];
		return 1;
	}
};

vector<tuple<int,int,int>> manhattanMST(vector<pt> a) { // grafo candidato a ser el MST
	int n = a.size();
	vector<int> id(n);
	iota(all(id), 0);
	vector<tuple<int,int,int>> edges;
	for (int k = 0; k < 4; k++) {
		sort(all(id), [&](int i, int j) {
			return (a[i] - a[j]).x < (a[j] - a[i]).y;
		});
		map<int, int> sweep;
		for (int i : id) {
			for (auto it = sweep.lower_bound(-a[i].y); it != sweep.end(); sweep.erase(it++)) {
				int j = it->second;
				pt d = a[i] - a[j];
				if (d.y > d.x) break;
				edges.emplace_back(d.y + d.x, i, j);
			}
			sweep[-a[i].y] = i;
		}
		for (pt &p : a) {
			int u = p.x, v = p.y;
			if (k & 1) p = pt(-u, v);
			else p = pt(v, u);
		}
	}
	return edges;
}

pt read() {
	int p,q;
	cin >> p >> q;
	return pt(p, q);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	
	int n; cin >> n;
	vector<pt> a(n);
	for (pt &p : a) p = read();
	auto edges = manhattanMST(a);
	
	// Building real MST
	sort(all(edges));
	ll ans = 0;
	DSU dsu(n);
	vector<pair<int,int>> res;
	for (auto [d, i, j] : edges) {
		if (dsu.join(i, j)) {
			ans += d;
			res.emplace_back(i, j);
		}
	}

	cout << ans << "\n";
	for (auto [i, j] : res) cout << i << " " << j << "\n";

	return 0;
}

// https://judge.yosupo.jp/submission/405024

