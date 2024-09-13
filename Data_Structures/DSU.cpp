#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

struct DSU {
    int n;
    vector<int> par, size;
    void init(int n) {
        par.resize(n);
        size.assign(n, 1);
        iota(all(par), 0);
    }
    int get(int a) {
        return (a == par[a]) ? a : par[a] = get(par[a]);
    }
    bool join(int a, int b) {
        a = get(a), b = get(b);
        if (a == b) return 0;
        if (size[a] < size[b]) swap(a,b);
        par[b] = a;
        size[a] += size[b];
        return 1;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n,m;
    cin >> n >> m;
    DSU dsu(n);
    while(m--) {
        int a,b;
        string op;
        cin >> op >> a >> b;
        a--; b--;
        if (op == "union") {
            dsu.join(a,b);
        }
        else {
            cout << (!dsu.join(a,b) ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
