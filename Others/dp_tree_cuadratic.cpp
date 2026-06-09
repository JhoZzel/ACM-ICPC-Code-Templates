#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int N = 5000 + 5;

int n;
int sz[N];
ll dp[N][N];
vector<int> G[N];

void dfs(int u, int p) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    
    sz[u] = 1;

    for (int v : G[u]) if (v != p) {
        dfs(v, u);

        vector<ll> add(sz[u] + sz[v] + 1, 0);
        for (int i = 1; i <= sz[u]; i++) {
            for (int j = 1; j <= sz[v]; j++) {
                add[i + j] += dp[u][i] * dp[v][j] % MOD;
                add[i + j] %= MOD;
            }
        }

        sz[u] += sz[v];
        
        for (int i = 1; i <= sz[u]; i++) {
            dp[u][i] += add[i];
            dp[u][i] %= MOD;
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    dfs(0, 0);
    
    for (int k = 1; k <= n; k++) {
        ll acc = 0;
        for (int i = 0; i < n; i++) {
            acc += dp[i][k];
            acc %= MOD;
        }
        cout << acc << '\n';
    }

    return 0;
}


