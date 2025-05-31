#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 1e18;
const int N = 3000 + 5;

int n,K;
int a[N];
int pre[N];
ll dp[N][N];

// opt(i - 1, k) <= opt(i, k)
ll cost(int i, int j) { 
    ll sa = pre[j] - pre[i - 1];
    return sa * sa;
}

void go(int l, int r, int k, int opl = 1, int opr = n) {
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<ll, int> mn = {INF, mid};
    for (int j = opl; j <= min(mid, opr); j++) {
        mn = min(mn, pair{dp[j - 1][k - 1] + cost(j, mid), j});
    }
    int opt = mn.second;
    dp[mid][k] = mn.first;

    go(l, mid - 1, k, opl, opt);
    go(mid + 1, r, k, opt, opr);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> K;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dp[i][j] = INF;

    dp[0][0] = 0;

    for (int k = 1; k <= K; k++) go(1, n, k);
    
    cout << dp[n][K] << "\n";

    return 0;
}

// https://cses.fi/problemset/result/13125422/

