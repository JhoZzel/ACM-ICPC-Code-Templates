#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

const int N = 1e2 + 5;
const int MAX_V = 1e5 + 5;
const int INF = 1e9 + 5;

int main() {
    int n,C;
    cin >> n >> C;
    int w[n], v[n];
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];
    int dp[N][MAX_V];
    dp[n][0] = 0;
    for (int val = 1; val < MAX_V; val++) dp[n][val] = INF;
    for (int pos = n - 1; pos >= 0; pos--) {
        for (int val = 0; val < MAX_V; val++) {
            dp[pos][val] = dp[pos + 1][val];
            if (val - v[pos] >= 0) {
                dp[pos][val] = min(dp[pos + 1][val], dp[pos + 1][val - v[pos]] + w[pos]);
            }
        }
    }
    for (int max_val = MAX_V - 1; max_val >= 0; max_val--) {
        if (dp[0][max_val] <= C) {
            cout << max_val << "\n";
            return 0;
        }
    }
    return 0;
}

