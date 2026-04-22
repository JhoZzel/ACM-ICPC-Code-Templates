// Trie
//

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int LOG = 61;
const int N = 1e5 + 5;  

struct Trie{ 
    int nodes = 0;
    vector<vector<int>> trie;

    Trie(int n) : trie((n + 5) * LOG, vector<int>(2, 0)) {}

    void add(ll x) { // Insert X in the trie
        int r = 0;
        for (int i = LOG - 1; i >= 0; i--) {
            int ch = (x >> i) & 1;
            if (!trie[r][ch]) trie[r][ch] = ++nodes;
            r = trie[r][ch];
        }
    }

    ll query(ll x) { // max(X XOR Y) when Y is in the trie
        ll ans = 0;
        int r = 0;
        for (int i = LOG - 1; i >= 0; i--) {
            int ch = (x >> i) & 1;
            if (trie[r][ch ^ 1]) {
                ans += (1ll << i);
                r = trie[r][ch ^ 1];
            } 
            else r = trie[r][ch];
        }
        return ans;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;

    Trie t(n);
    t.add(1632);
    t.add(1124);
    t.add(443);
    t.add(2121);

    cout << t.query(2003) << '\n';
        
    return 0;
}
