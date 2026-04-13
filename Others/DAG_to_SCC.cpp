#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
 
const int N = 5e5 + 5;
 
int n,m,nc;
bool vis[N];
int c[N], in[N], out[N];
vector<int> GG[N], G[2][N];
vector<vector<int>> SCC;
 
void dfs(int id, int u, vector<int> &z) {
    vis[u] = 1;
    for (int v : G[id][u]) {
        if (vis[v]) continue;
        dfs(id, v, z);
    }
    z.push_back(u);
}

int dfs_match(int u) {
    if (vis[u]) return -1;
    vis[u] = 1;
    if (out[u] == 0) return u;
    for (int v : GG[u]) {
        int to = dfs_match(v);
        if (to != -1) return to;
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[0][u].push_back(v);
        G[1][v].push_back(u);
    }
 
    vector<int> order;
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(0, i, order);
    reverse(all(order));
 
    fill(vis, vis + n, 0);
    for (int u : order) {
        if (vis[u]) continue;
        vector<int> comp;
        dfs(1, u, comp);
        for (int v : comp) c[v] = nc;
        SCC.push_back(comp);
        nc++;
    }
    
    // Build condensed graph
    for (int i = 0; i < n; i++) {
        for (int j : G[0][i]) {
            if (c[i] == c[j]) continue;
            in[c[j]] += 1;
            out[c[i]] += 1;
            GG[c[i]].push_back(c[j]);
        }
    }
    
    // Strong connectivity augmentation problem
    // Make the DAG GG to a big one SCC
    
    if (nc == 1) {
        cout << "0\n";
        return 0;
    }
    
    // matched_sources[i] can reach matched_sinks[i]
    // Every source in never_matched_sources can reach at least one sink in matched_sinks.
    // Every sink in never_matched_sinks can be reached by at least one source in matched_sources.
    
    vector<int> matched_sources, matched_sinks;
    vector<int> never_matched_sources, never_matched_sinks;
 
    fill(vis, vis + nc, 0);

    for (int i = 0; i < nc; i++) if (in[i] == 0) {
        // s -> source  t -> sink
        int s = i, t = dfs_match(s);
        if (t != -1) {
            matched_sources.push_back(s);
            matched_sinks.push_back(t);
        } else {
            never_matched_sources.push_back(s);
        }
    }
 
    // unmatched sinks
    for (int i = 0; i < nc; i++) {
        if (out[i] == 0 and !vis[i]) {
            never_matched_sinks.push_back(i);
        }
    }
 
    vector<int> sources, sinks;
    
    sources.insert(sources.end(), all(matched_sources));
    sources.insert(sources.end(), all(never_matched_sources));
 
    sinks.insert(sinks.end(), all(matched_sinks));
    sinks.insert(sinks.end(), all(never_matched_sinks));
 
    int P = matched_sources.size();
    int N = sources.size();
    int M = sinks.size();
    int K = min(N, M);
 
    vector<pair<int,int>> edges; // sink to source id's
 
    if (P) {
        edges.emplace_back(0, P - 1);
        for (int i = 1; i < P; i++) edges.emplace_back(i, i - 1);
    }
    for (int i = P; i < K; i++) edges.emplace_back(i, i);
    for (int i = K; i < N; i++) edges.emplace_back(0, i);
    for (int i = K; i < M; i++) edges.emplace_back(i, 0);


    cout << sz(edges) << '\n';
    for (auto [i, j] : edges) {
        int u = sinks[i], v = sources[j];
        cout << SCC[u][0] + 1 << " " << SCC[v][0] + 1 << '\n';
    }
 
    return 0;
}
