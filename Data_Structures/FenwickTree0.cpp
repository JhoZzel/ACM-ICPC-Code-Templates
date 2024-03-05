#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
using namespace std;
typedef long long ll;

struct FenwickTree { // 1-indexed
    int n; 
    vector<ll> ft;

    FenwickTree(const vector<int> &a) {
        n = a.size();
        ft = vector<ll>(n + 1, 0);
        for (int i = 0; i < n; i++) {
            update(i + 1, a[i]);
        }
    }

    void update(int pos, ll x) { // a[pos] += x
        while(pos <= n) {
            ft[pos] += x;
            pos += (-pos) & pos;
        }
    }
    
    ll query(int pos) { 
        ll res = 0;
        while(pos > 0) {
            res += ft[pos];
            pos &= pos - 1; // pos -= LSO(pos)
        }
        return res;
    }

    ll query(int l, int r) { 
        return query(r) - query(l - 1);
    }

    ll at(int pos) { 
        return query(pos) - query(pos - 1);
    }
};

int main() {
    fast_io;
    int n,m; 
    cin >> n >> m;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    FenwickTree FT(a);
    while(m--) {
        int t,x,y;
        cin >> t >> x >> y;
        if (t == 0) {
            cout << FT.query(x,y) << "\n";
        }
        else {
            FT.update(x, y - FT.at(x));
        }
    }
    return 0;
}
