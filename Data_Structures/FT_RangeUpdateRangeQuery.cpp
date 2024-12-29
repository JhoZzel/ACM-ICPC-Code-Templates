#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 5e5 + 5;

ll FT[2][N];

void update(int id, int i, ll x) {
    for (; i < N; i += i & -i) FT[id][i] += x;
}

ll sum(int id, int i) {
    ll sa = 0;
    for (; i; i -= i & -i) sa += FT[id][i];
    return sa;
}

void update_range(int l, int r, int x) {
    update(0, l, x);
    update(0, r + 1, -x);

    update(1, l, 1ll * x * (l - 1));
    update(1, r + 1, -1ll * r * x);
}

ll query_range(int l, int r) {
    ll p = r * sum(0, r) - sum(1, r);
    ll q = (l - 1) * sum(0, l - 1) - sum(1, l - 1);
    return p - q;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n,q;
    cin >> n >> q;
    while(q--) {
        int op,l,r;
        cin >> op >> l >> r;
        if (op == 1) {
            int x; cin >> x;
            update_range(l, r, x);
        } else {
            cout << query_range(l, r) << '\n';
        }
    }
    return 0;
}
