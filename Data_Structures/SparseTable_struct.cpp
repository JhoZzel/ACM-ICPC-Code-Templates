#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<int>> st;
 
    int f(int a, int b) { return min(a, b); }

    SparseTable(vector<int> &a) { // 0-indexed
        int n = a.size();
        int k = __lg(n) + 1;
        st.resize(n, vector<int>(k));
        for (int i = 0; i < n; i++) st[i][0] = a[i];
        for (int p = 1, d = 1; 2 * d <= n; p++, d <<= 1) {
            for (int i = 0; i + 2 * d <= n; i++) {
                st[i][p] = f(st[i][p - 1], st[i + d][p - 1]);
            }
        }
    }
    
    int query(int l, int r) {
        int k = __lg(r - l + 1);
        int d = (1 << k);
        return min(st[l][k], st[r - d + 1][k]);
    }

    /*int query(int l, int r) {
        int len = r - l + 1;
        int mn = INT_MAX;
        while(len) {
            int k = __lg(len);
            mn = f(mn, st[l][k]);
            l += (1 << k);
            len ^= (1 << k);
        }
        return mn;
    }*/
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    SparseTable st(a);
    while(q--) {
        int l,r;
        cin >> l >> r;
        r--;
        cout << st.query(l, r) << endl;
    }

    return 0; 
}

// https://judge.yosupo.jp/submission/289250
