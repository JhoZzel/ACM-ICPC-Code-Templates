#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct node {
    int mx,freq;

    node() : mx(-1), freq(0) {}
    node(int x) : mx(x), freq(1) {}

	node operator + (node R) {
		node L = *this;
        node q;
        if (L.mx > R.mx) q = L;
        else if (R.mx > L.mx) q = R;
        else {
            q.mx = L.mx;
            q.freq = L.freq + R.freq;
        }
		return q;
	}
};

struct DisjointST {
    vector<node> dp[32];

    DisjointST() {}
    DisjointST(vector<int> &arr){
        int i, c, h, l, n = (int)arr.size();
        vector<node> a(n);
        for (int i = 0; i < n; i++) a[i] = node(arr[i]);
        for (h = 0; h <= __lg(n); h++){
            dp[h].resize(n + 1);
            for (c = l = 1 << h; c < n + l; c += (l << 1)){
                for (i = c + 1; i <= min(n, c + l); i++){
                    dp[h][i] = dp[h][i - 1] + a[i - 1];
                }
                for (i = min(n, c) - 1; i >= c - l; i--){
                    dp[h][i] = a[i] + dp[h][i + 1];
                }
            }
        }
    }

    node query(int l, int r){
        int h = __lg(l ^ (r + 1));
        return dp[h][l] + dp[h][r + 1];
    }
}; 

const int MOD = 1e9 + 7;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int &e : a) cin >> e;

    DisjointST dST(a);

    int q,x,y,z,t;
    cin >> q >> x >> y >> z >> t;

    ll last = 0;
    int ans = 1;
    while(q--) {
        int l = (last * x + y) % n;
        int r = (last * z + t) % n;
        if (l > r) swap(l, r);
        last = dST.query(l, r).freq;
        ans = (ans * last) % MOD;
    }
    cout << ans << '\n';

	return 0;
}	

// https://codeforces.com/group/1rv4rhCsHp/contest/102954/submission/333033011
