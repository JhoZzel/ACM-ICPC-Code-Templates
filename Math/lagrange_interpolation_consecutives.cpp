#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

ll bpow(ll a, ll e) {
    ll r = 1;
    while(e) {
        if (e & 1) r = r * a  % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

const int N = 1e5 + 10;

ll F[N], Fi[N];
ll pre[N], suf[N];

int main() {
    cin.tie(0) -> sync_with_stdio(0);
        
    F[0] = 1;
    for (int i = 1; i < N; i++) F[i] = F[i - 1] * i % MOD;
    Fi[N - 1] = bpow(F[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) Fi[i] = (i + 1) * Fi[i + 1] % MOD;
   
    int n; cin >> n;
    vector<int> y(n + 1);
    for (int i = 0; i <= n; i++) cin >> y[i];

    int x; cin >> x;
    
    pre[0] = 1;
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] * (x - i + MOD) % MOD;
    suf[n] = 1;
    for (int i = n; i > 0; i--) suf[i - 1] = suf[i] * (x - i + MOD) % MOD;

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        int sg = (n - i) % 2 == 0 ? 1 : -1;
        ll add = sg * y[i] * pre[i] % MOD * suf[i] % MOD * Fi[i] % MOD * Fi[n - i] % MOD;
        ans = (ans + add + MOD) % MOD;
    }
    cout << ans << '\n';

    return 0;
}

// https://atcoder.jp/contests/arc033/tasks/arc033_4
