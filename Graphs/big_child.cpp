#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;

int n;
int c[N];
int timer;
ll ans[N], sum[N];
int mx_freq, cnt[N], freq[N];
int tin[N], tout[N], who[N], sz[N];
vector<int> G[N];

void pre_dfs(int u, int p) {
    tin[u] = timer++;
    who[tin[u]] = u; 
    sz[u] = 1;
    for (int v : G[u]) if (v != p) {
        pre_dfs(v, u);
        sz[u] += sz[v];
    }
    tout[u] = timer - 1;
}

void add(int u, int d) {
    int x = c[u];
    sum[freq[x]] -= x;
    cnt[freq[x]] -= 1;
    freq[x] += d;
    cnt[freq[x]] += 1;
    sum[freq[x]] += x;
    mx_freq = max(mx_freq, freq[x]);
}

ll query() {
    while(cnt[mx_freq] == 0) mx_freq--;
    return sum[mx_freq];
}

void dfs(int u, int p, bool keep) {    
    int big = -1;
    for (int v : G[u]) if (v != p) { // idetify the big child
        if (big == -1 or sz[v] > sz[big]) big = v;
    }
    for (int v : G[u]) if (v != p and v != big) {
        dfs(v, u, 0); // run a dfs on small childs and clear them from cnt
    }
    if (big != -1) dfs(big, u, 1); //  dfs on bigChild not cleared from cnt, keep values
    
    // Now we have info just about the big child
    // Add the info about the node u
    add(u, 1);
    for (int v : G[u]) if (v != p and v != big) {
        for (int t = tin[v]; t <= tout[v]; t++) { // Add the info about the small nodes
            add(who[t], 1);
        }
    }

    // the arrays have the information updates for the node u, you can answer queries easily
    ans[u] = query();

    if (!keep) { // clear all the subtree?
        for (int t = tin[u]; t <= tout[u]; t++) {
            add(who[t], -1);
        }
    }
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
    
    cin >> n;
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 1; i < n; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    pre_dfs(0, 0);
    dfs(0, 0, 1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';
    
	return 0;
}
