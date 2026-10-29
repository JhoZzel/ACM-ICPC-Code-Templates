#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

using ll = long long;

#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); ++i)


/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: $O(F E \log(V))$ where F is max flow. $O(VE)$ for setpi.
 */


const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
	struct edge {
		int from, to, rev;
		ll cap, cost, flow;
	};
	int N;
	vector<vector<edge>> ed;
	vector<int> seen;
	vector<ll> dist, pi;
	vector<edge*> par;

	MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		if (from == to) return;
		ed[from].push_back(edge{ from, to, sz(ed[to]), cap, cost, 0 });
		ed[to].push_back(edge{ to, from, sz(ed[from]) - 1, 0, -cost, 0 });
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end())
						its[e.to] = q.push({ -dist[e.to], e.to });
					else
						q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) { // siempre busca el max flujo 
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);

			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		rep(i,0,N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
		return {totflow, totcost / 2};
	}

	// Si algunos costos pueden ser negativos, llamar a esta función antes de maxflow:
	void setpi(int s) {
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
				for (edge& e : ed[i]) if (e.cap)
					if ((v = pi[i] + e.cost) < pi[e.to])
						pi[e.to] = v, ch = 1;
		assert(it >= 0); // Ciclo de costo negativo detectado
	}
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n,m,k;
	cin >> n >> m >> k;
	MCMF g(n + 1);
	for (int i = 0; i < m; i++) {
		int a,b,r,c;
		cin >> a >> b >> r >> c;
		g.addEdge(a, b, r, c);
	}
	g.addEdge(0, 1, k, 0);
	auto [flow, cost] = g.maxflow(0, n);
	if (flow != k) cout << "-1\n";
	else cout << cost << "\n";

	return 0;
}

// https://cses.fi/problemset/result/19227033/

