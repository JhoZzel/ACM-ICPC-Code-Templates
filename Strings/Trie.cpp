#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;  
const int LOG = 31;
const int E = 2;

struct Trie { 
    int nodes = 0;
    int trie[N * LOG][E];

    void add(int x) { // Insert X in the trie
        int r = 0;
        for (int i = LOG - 1; i >= 0; i--) {
            int ch = (x >> i) & 1;
            if (!trie[r][ch]) trie[r][ch] = ++nodes;
            r = trie[r][ch];
        }
    }

    int query(int x) { // max(X XOR Y) when Y is in the trie
        int ans = 0;
        int r = 0;
        for (int i = LOG - 1; i >= 0; i--) {
            int ch = (x >> i) & 1;
            if (trie[r][1 - ch]) {
                ans += (1ll << i);
                r = trie[r][1 - ch];
            } 
            else r = trie[r][ch];
        }
        return ans;
    }
} T;


int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n; cin >> n;
    int pre = 0;
    int ans = 0;
    T.add(0);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        pre ^= x;
        ans = max(ans, T.query(pre));
        T.add(pre);
    }
    cout << ans << '\n';

    return 0;
}
