#include<bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()

using ll = long long;

const ll INF = 1e18;

struct Dinic { // 0-indexed
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};

	vector<int> lvl, p, q; // p = pointer
	vector<vector<Edge>> g;

	Dinic(int n) : lvl(n), p(n), q(n), g(n) {} 

	void add_edge(int a, int b, ll c, ll rcap = 0) {
		g[a].push_back({b, sz(g[b]), c, c});
		g[b].push_back({a, sz(g[a]) - 1, rcap, rcap});
	}

	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = p[v]; i < sz(g[v]); i++) {
			Edge& e = g[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, g[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}

	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		for(int L = 0; L < 31; L++) do { // 'int L = 30' maybe faster for random data
			lvl = p = vector<int>(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : g[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, INF)) flow += p;
		} while (lvl[t]);
		return flow;
	}

	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n,m;
    cin >> n >> m;
    Dinic d(n);
    for (int i = 0; i < m; i++) {
        int u,v,c;
        cin >> u >> v >> c;
        u--; v--;
        d.add_edge(u,v,c);
    }

    cout << d.calc(0, n - 1) << '\n';

    return 0;
}

// https://cses.fi/problemset/result/13780607/
