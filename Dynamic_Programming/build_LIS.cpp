#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define ff first
#define ss second

using ll = long long;

const int INF = 1e9 + 5;

vector<int> build_LIS(vector<int> &a) { 
    const int n = a.size();
    vector<pair<int,int>> d(n + 1, {INF, -1});
    vector<int> par(n, -1);
    d[0] = {-INF,-1};
   
    for (int i = 0; i < n; i++) {
        int j = lower_bound(all(d), pair{a[i], -INF}) - d.begin();
        if (a[i] < d[j].ff and d[j - 1].ff < a[i]) {
            d[j] = {a[i], i};
            par[i] = d[j - 1].ss;
        }
    }

    int len = n;
    while(d[len].ff == INF) len--;
    int u = d[len].ss;

    vector<int> lis;
    while (u != -1) {
        lis.push_back(u);
        u = par[u];
    }
    reverse(all(lis));

    return lis;
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    vector<int> lis = build_LIS(a);
    cout << lis.size() << '\n';
    for (int x : lis) cout << x << ' ';
    cout << '\n';
    return 0;
}
