#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
using namespace std;

const int INF = 1e9 + 5;
const int N = 1e2 + 5;
const int W = 1e4 + 5;

int n,C;
int v[N];
int w[W];
int dp[N][W];
bool vis[N][W];
vector<int> sol;

int DP(int pos, int cap) {
    if (cap < 0) return -INF;
    if (pos == n) return 0;
    if (vis[pos][cap]) return dp[pos][cap];
    vis[pos][cap] = true;
    return dp[pos][cap] = max(DP(pos + 1, cap), DP(pos + 1, cap - w[pos]) + v[pos]);
}

void rec(int pos, int cap) {
    if (pos == n) return;
    if (DP(pos, cap) == DP(pos + 1, cap)) return rec(pos + 1, cap);
    else {
        sol.push_back(pos);
        return rec(pos + 1, cap - w[pos]);
    }
}

int main() {
    fast_io;
    cin >> n >> C;
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];
    rec(0,C);
    cout << "Solucion optima:\n";
    for (int i : sol) {
        cout << "i = " << i << "\tv[i] = " << v[i] << "\tw[i] = " << w[i] << endl;
    }
    cout << "Rpta: " << DP(0,C) << endl;
    return 0;
}



