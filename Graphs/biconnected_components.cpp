#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const int N = 5e5 + 5; 

int n, m;
int dp[N], bck_hit[N];
int color[N];
stack<pair<int, int>> st;
vector<vector<int>> bcc;
vector<pair<int,int>> G[N];

void dfs_fft(int u, int p_id = -1) { 
	color[u] = 1;
	for (auto [v, id] : G[u]) {
		if (id == p_id) continue;

		if (color[v] == 1) { 
			dp[u] += 1;
			dp[v] -= 1;
			bck_hit[v] += 1; 
			st.emplace(u, v);
		} else if (color[v] == 0) {
			st.emplace(u, v);

			int hits_before = bck_hit[u];
			dfs_fft(v, id);
			int hits_from_v = bck_hit[u] - hits_before;
			dp[u] += dp[v];

			// Condición: ningún back-edge del subárbol salta por encima de u.
			// Esto significa que acabamos de aislar una componente biconexa.
			if (dp[v] == hits_from_v) {
				vector<int> comp;
				pair<int,int> edge;
				// Sacamos aristas de la pila hasta llegar a la arista (u, v) que inició esta rama
				do {
					edge = st.top();
					st.pop();
					comp.emplace_back(edge.first);
					comp.emplace_back(edge.second);
				} while (edge != make_pair(u, v));

				sort(all(comp));
				comp.erase(unique(all(comp)), comp.end());
				bcc.emplace_back(comp);
			}
		}
	}
	color[u] = 2;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; 
		cin >> u >> v;  // 0-indexed
		G[u].emplace_back(v, i);
		G[v].emplace_back(u, i);
	}

	for (int i = 0; i < n; i++) {
		if (color[i]) continue;
		if (G[i].empty()) {
			bcc.push_back({i}); // Un nodo totalmente aislado es una componente biconexa trivial por sí solo
			color[i] = 2;
		} else {
			dfs_fft(i);
		}
	}

	cout << sz(bcc) << "\n";
	for (auto &comp : bcc) {
		cout << sz(comp) << " ";
		for (int u : comp) cout << u << " ";
		cout << "\n";
	}

	return 0;
}
