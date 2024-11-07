#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
using namespace std;
typedef long long ll;

const int N = 1e2 + 5;
const int W = 1e4 + 5;

int main() {
    fast_io; 
    int n,C;
    cin >> n >> C;
    int v[N], w[N];
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];
    int dp[N][W] = {};
    for (int cap = 0; cap <= C; cap++) {
        for (int pos = n - 1; pos >= 0; pos--) {
            dp[pos][cap] = dp[pos + 1][cap];
            if (cap - w[pos] >= 0) {
                dp[pos][cap] = max(dp[pos + 1][cap], dp[pos + 1][cap - w[pos]] + v[pos]);
            }
        }
    }
    cout << dp[0][C] << "\n"; 
    return 0;
}


