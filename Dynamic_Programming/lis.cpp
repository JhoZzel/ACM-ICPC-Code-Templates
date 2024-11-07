#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie (0); cout.tie(0)
#define all(x) (x).begin(), (x).end()
using namespace std;

const int INF = 1e9 + 5;

int LIS(vector<int> &a) {
    const int n = a.size();
    vector<int> d(n + 1,INF);
    d[0] = -INF;
    for (int i = 0; i < n; i++) {
        int l = upper_bound(all(d), a[i]) - d.begin();
        if (d[l - 1] < a[i]) {
            d[l] = min(d[l], a[i]);
        }
    }
    for (int l = n; l >= 1; l--) {
        if (d[l] < INF) return l;
    }
    return 1;
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << LIS(a) << "\n";
    return 0;
}
