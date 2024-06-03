#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

struct FenwickTree {
    ll t[N];
    void update(int i, ll x) {
        for (; i < N; i += i & -i) t[i] += x;
    }
    ll sum(int i) {
        ll sa = 0;
        for (; i > 0; i -= i & -i) sa += t[i];
        return sa;
    }
    ll query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

FenwickTree FT; 

int main() {
    int n,q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        FT.update(i, x);
    }
    while(q--) {
        int t,x,y;
        cin >> t >> x >> y;
        if (t) {
            ll at = FT.query(x,x); 
            FT.update(x, y - at);
        }
        else {
            cout << FT.query(x,y) << '\n';
        }
    }
    return 0;
}
