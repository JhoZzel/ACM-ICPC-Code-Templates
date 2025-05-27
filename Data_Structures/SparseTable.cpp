#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
const int LOG = 20;

int n,q;
int a[N];
int st[N][LOG];

int f(int a, int b) {
    return min(a, b);
}

void build() {
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
    return f(st[l][k], st[r - d + 1][k]);
}

/*
int query(int l, int r) {
    int len = r - l + 1;
    int mn = INT_MAX;
    while(len) {
        int k = __lg(len);
        mn = f(mn, st[l][k]);
        l += (1 << k);
        len ^= (1 << k);
    }
    return mn;
}
*/

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    build();
    while(q--) {
        int l,r;
        cin >> l >> r;
        r--;
        cout << query(l, r) << endl;
    }

    return 0; 
}

// https://judge.yosupo.jp/submission/289251
// https://judge.yosupo.jp/submission/289253
