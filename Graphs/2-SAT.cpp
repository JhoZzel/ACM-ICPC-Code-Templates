#include <bits/stdc++.h>
using namespace std;

struct SAT { // 0-indexed
    int n;
    vector<bool> vis;
    vector<int> order;
    vector<int> comp;
    vector<int> component;
    vector<vector<int>> G[2];
    
    SAT(int n) : n(n) {
        comp.resize(2 * n);
        vis.assign(2 * n, false);
        G[0].assign(2 * n, vector<int> ());
        G[1].assign(2 * n, vector<int> ());
    }

    void add_edge(int u, int v) { // u OR v
        //  u -> 2i
        // ~u -> 2i + 1
        G[0][u ^ 1].emplace_back(v);
        G[0][v ^ 1].emplace_back(u);
        G[1][v].emplace_back(u ^ 1);
        G[1][u].emplace_back(v ^ 1);
    }
    
    void dfs(int u, int id) {
        vis[u] = true;
        for (int v : G[id][u]) {
            if (vis[v]) continue;
            dfs(v, id);
        }
        (id ? component : order).push_back(u);
    }

    void get_SCC() {
        for (int u = 0; u < 2 * n; u++) {
            if (vis[u]) continue;
            dfs(u, 0);
        }
        reverse(order.begin(), order.end());
        vis.assign(2 * n, false);
        int component_id = 0;
        for (int u : order) {
            if (vis[u]) continue;
            dfs(u, 1);
            for (int x : component) {
                comp[x] = component_id;
            }
            component_id++;
            component.clear();
        }
    }

    vector<int> solve() {
        vector<int> res(n);
        get_SCC();
        for (int i = 0; i < n; i++) {
            int val = 2 * i;
            if (comp[val] == comp[val ^ 1]) return vector<int>();
            if (comp[val] < comp[val ^ 1]) res[i] = 0;
            if (comp[val] > comp[val ^ 1]) res[i] = 1;
        }
        return res;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    SAT Solver(n);
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        u--; v--;
        if (w == 1) {
            Solver.add_edge(2 * u, 2 * v + 1);
            Solver.add_edge(2 * u + 1, 2 * v);
        } else {
            Solver.add_edge(2 * u, 2 * v);
            Solver.add_edge(2 * u + 1, 2 * v + 1);
        }
    }

    vector<int> res = Solver.solve();
    if (res.empty()) cout << "Impossible\n";
    else {
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (res[i]) ans.push_back(i);
        }
        cout << ans.size() << "\n";
        for (int u : ans) cout << ++u << " ";
        cout << '\n';
    }
    return 0;
}
