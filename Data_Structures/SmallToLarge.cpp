#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;

int n;
int c[N];
int par[N];
ll ans[N];
ll sum[N];
int mx[N];
map<int, int> mp[N];
vector<int> G[N];

int get(int u) {
    return (u == par[u]) ? u : par[u] = get(par[u]);
}

void merge(int u, int v) {
    u = get(u); v = get(v);
    if (mp[u].size() > mp[v].size()) swap(u, v);
    for (auto [c, f] : mp[u]) { // u -> v
        mp[v][c] += f;
        if (mp[v][c] == mx[v]) sum[v] += c;
        else if (mp[v][c] > mx[v]) {
            mx[v] = mp[v][c];
            sum[v] = c;
        }
    }
    mp[u].clear();
    par[u] = v;
}

void dfs(int u, int p = 0) { 
    for (int v : G[u]) {
        if (v == p) continue;
        dfs(v, u);
        merge(u, v);
    }
    ans[u] = sum[get(u)];
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        mp[i][c[i]]++;
        sum[i] = c[i];
        mx[i] = 1;
        par[i] = i;
    }

    for (int i = 1; i < n; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    
    dfs(0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
