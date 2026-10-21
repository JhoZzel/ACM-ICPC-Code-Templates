// Dinic
//

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;

const ll INF = 1e18;

struct Dinic {
	struct Edge {
		int to,rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0ll); } 
	};

	vector<int> lvl, ptr, q;
	vector<vector<Edge>> g;

	Dinic(int n) : lvl(n), ptr(n), q(n), g(n) {}

	void add_edge(int a, int b, ll c, ll rcap = 0) {
		g[a].push_back({b, sz(g[b]), c, c});
		g[b].push_back({a, sz(g[a]) - 1, rcap, rcap});
	}

	ll dfs(int v, int t, ll f) {
		if (v == t or !f) return f;
		for (int &i = ptr[v]; i < sz(g[v]); i++) {
			Edge &e = g[v][i];
			if (lvl[e.to] == lvl[v] + 1) 
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, g[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) { // returns the increment in the flow from s to t
		ll flow = 0; q[0] = s;
		for (int L = 0; L < 31; L++) do { // 'int L = 30' maybe faster for random data
			lvl = ptr = vector<int>(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while(qi < qe and !lvl[t]) {
				int v = q[qi++];
				for (Edge e : g[v]) 
					if (!lvl[e.to] and (e.c >> (30 - L))) 
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while(ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while(lvl[t]);
		return flow;
	}

	bool leftOfMinCut(int a) { return lvl[a] != 0; } 
	
};

// MVC
// 1. Nodos de la partición IZQUIERDA (L) que NO están en leftOfMinCut
for (int i = 1; i <= N; i++) { // asumiendo nodos de L van de 1 a N
    if (!d.leftOfMinCut(i)) {
        mvc.push_back(i);
    }
}

// 2. Nodos de la partición DERECHA (R) que SÍ están en leftOfMinCut
for (int j = N + 1; j <= N + M; j++) { // asumiendo nodos de R van de N+1 a N+M
    if (d.leftOfMinCut(j)) {
        mvc.push_back(j);
    }
}
