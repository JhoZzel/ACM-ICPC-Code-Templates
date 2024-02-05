#include <bits/stdc++.h>
using namespace std;

struct SATSolver {
    int n;
    int m;
    vector<bool> vis;
    vector<int> order;
    vector<int> comp;
    vector<int> component;
    vector<vector<int>> G;
    vector<vector<int>> Gt;
    
    SATSolver(int n, int m) : n(n), m(m) {
        // x_i = 2i
        // ~x_i = 2 * i + 1
        comp.resize(2 * n);
        vis.assign(2 * n, false);
        G.assign(2 * n, vector<int> ());
        Gt.assign(2 * n, vector<int> ());
    }

    void add_edge(int u, int v) {
        // u OR v
        G[u ^ 1].emplace_back(v);
        G[v ^ 1].emplace_back(u);
        Gt[v].emplace_back(u ^ 1);
        Gt[u].emplace_back(v ^ 1);
    }

    void DFS1(int u) {
        vis[u] = true;
        for (int w : G[u]) {
            if (vis[w]) continue;
            DFS1(w);
        }
        order.push_back(u);
    }
    
    void DFS2(int u) {
        vis[u] = true;
        for (int w : Gt[u]) {
            if (vis[w]) continue;
            DFS2(w);
        }
        component.push_back(u);
    }
    
    void get_SCC() {
        for (int i = 0; i < 2 * n; i++) {
            if (vis[i]) continue;
            DFS1(i);
        }
        reverse(order.begin(), order.end());
        vis.assign(2 * n, false);
        int component_id = 0;
        for (int i : order) {
            if (vis[i]) continue;
            DFS2(i);
            for (int x : component) comp[x] = component_id;
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
    int n, m;
    cin >> n >> m;
    SATSolver Solver(n,m);
    for (int i = 0; i < m; i++) {
        // Se lee 1-indexed
        // x_i = i
        // ~x_i = -i
        int u, v;
        cin >> u >> v;
        if (u < 0) {
            u = -u;
            u--;
            u = 2 * u + 1;
        }
        else {
            u--;
            u *= 2;
        }

        if (v < 0) {
            v = -v;
            v--;
            v = 2 * v + 1;
        }
        else {
            v--;
            v *= 2;
        }

        Solver.add_edge(u,v);
    }

    vector<int> res = Solver.solve();
    if (res.empty()) cout << "There is no solution\n";
    else {
        cout << "One possible solution is:\n";
        for (int x : res) cout << x << " ";
    }
    return 0;
}
