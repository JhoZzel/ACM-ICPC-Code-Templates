#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

const int K = 4;

struct node {
    vector<pair<int,int>> b;
    node() {}
    node(int x) {
        b.emplace_back(x, 1);
    }
    node operator + (node other) {
        node q = *this;
        for (auto [y, cnt2] : other.b) {
            bool found = 0;
            int mn = 1e9;
            for (auto &[x, cnt1] : q.b) {
                mn = min(mn, cnt1);
                if (x == y) {
                    found = 1;
                    cnt1 += cnt2;
                }
            }
            if (found) continue;
            if ((int)q.b.size() < K) {
                q.b.emplace_back(y, cnt2);
            } else if (mn > cnt2) {
                for (auto &[x, cnt1] : q.b) {
                    cnt1 -= cnt2;
                }
            } else {
                vector<pair<int,int>> new_b;
                for (auto &[x, cnt1] : q.b) {
                    if (cnt1 == mn) continue;
                    new_b.emplace_back(x, cnt1 - mn);
                }
                if (mn != cnt2) new_b.emplace_back(y, cnt2 - mn);
                q.b = new_b;
            }
        }
        return q;
    }
};

const int N = 3e5 + 5;

int n,q;
int a[N];
node T[N];
node dp[22][N];
vector<int> pos[N];

void build() {
    int i, c, h, l;
    for (int i = 0; i < n; i++) T[i] = node(a[i]);
    for (h = 0; h <= __lg(n); h++){
        for (c = l = 1 << h; c < n + l; c += (l << 1)){
            for (i = c + 1; i <= min(n, c + l); i++){
                dp[h][i] = dp[h][i - 1] + T[i - 1];
            }
            for (i = min(n, c) - 1; i >= c - l; i--){
                dp[h][i] = T[i] + dp[h][i + 1];
            }
        }
    }
}

node query(int l, int r) {
    int h = __lg(l ^ (r + 1));
    return dp[h][l] + dp[h][r + 1];
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
   
    build();

    while(q--) {
        int l,r,k;
        cin >> l >> r >> k;
        l--; r--;
        node q = query(l, r);
        int mn = INT_MAX;
        for (auto [x, cnt] : q.b) {
            int lo = lower_bound(all(pos[x]), l) - pos[x].begin();
            int hi = upper_bound(all(pos[x]), r) - pos[x].begin();
            if ((hi - lo) * k > (r - l + 1)) {
                mn = min(mn, x);
            }
        }
        cout << (mn == INT_MAX ? -1 : mn) << '\n';
    }
	return 0;
}	

// https://codeforces.com/contest/840/submission/343067117
