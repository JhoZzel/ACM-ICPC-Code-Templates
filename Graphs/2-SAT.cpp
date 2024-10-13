#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define pv(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(20, '=') << endl

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define eb emplace_back
#define ff first
#define ss second

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
        int v[3] = {};
        for (int j = 0; j < 3; j++) {
            int u;
            char c;
            cin >> u >> c;
            u--;
            if (c == 'R') u *= 2;
            else u = 2 * u + 1;
            v[j] = u;
        }
        Solver.add_edge(v[0], v[1]);   
        Solver.add_edge(v[1], v[2]);   
        Solver.add_edge(v[0], v[2]);   
    }

    vector<int> res = Solver.solve();
    if (res.empty()) cout << "-1\n";
    else {
        for (int x : res) cout << (x ? "R" : "B");
        cout << '\n';
    }
    return 0;
}
