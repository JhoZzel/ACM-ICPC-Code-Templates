#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie (0); cout.tie(0)
#define dbg(x) do {cerr << #x <<" = " << (x) << endl; } while (false)
#define pr_v(x) for (int e : x) cout << e << " "; cout << "\n"
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int) x.size())
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int INF = 1e9 + 10;

int LIS(vi &a, int n) {
    vi dp(n + 1,INF);
    dp[0] = -INF;
    for (int i = 0; i < n; i++) {
        int l = upper_bound(all(dp), a[i]) - dp.begin();
        if (dp[l - 1] < a[i]) {
            dp[l] = min(dp[l], a[i]);
        }
    }

    int ans;
    for (int l = 0; l <= n; l++) {
        if (dp[l] < INF) ans = l;
    }

    return ans;
}

int main() {
    int n; cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << LIS(a, n) << "\n";
    return 0;
}

