#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n,m;
int in[N];
int out[N];
vector<int> G[N];
vector<int> path;

void dfs(int u) { // Hierholzer
    while(!G[u].empty()) {
        int v = G[u].back();
        G[u].pop_back();
        dfs(v);
    }
    path.push_back(u);
}

void solve() {
    int s = 0, t = 0;
    int st = 0;

    for (int i = 0; i < n; i++) {
        if (out[i] == in[i] + 1) s++, st = i;
        else if (in[i] == out[i] + 1) t++;
        else if (in[i] != out[i]) return;
    }

    if (!(s == 1 and t == 1) and !(s == 0 and t == 0)) return;

    dfs(st);

    reverse(path.begin(), path.end());

    if ((int)path.size() != m + 1) {
        path.clear();
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    while(cin >> n >> m) {
        if (n == 0 and m == 0) break;
        for (int i = 0; i < m; i++) {
            int u,v;
            cin >> u >> v;
            G[u].emplace_back(v);
            in[v] += 1;
            out[u] += 1;
        }

        solve();

        if (path.empty()) cout << "Impossible\n";
        else {
            for (int u : path) cout << u << ' ';
            cout << "\n";
        }
        for (int i = 0; i < n; i++) {
            in[i] = out[i] = 0;
            G[i].clear();
        }
        path.clear();
    }
    return 0;
}

// https://open.kattis.com/submissions/17640512
