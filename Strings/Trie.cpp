#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int LOG = 30;

int nodes;
int cnt[N * LOG];
int trie[N * LOG][2];

void add(int x, int d) { // Insert X in the trie
    int r = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        int ch = (x >> i) & 1;
        if (!trie[r][ch]) trie[r][ch] = ++nodes;
        r = trie[r][ch];
        cnt[r] += d;
    }
}

int query(int x) { // max(X XOR Y) when Y is in the trie
    int ans = 0;
    int r = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        int ch = (x >> i) & 1;
        if (cnt[trie[r][ch ^ 1]]) {
            ans |= (1 << i);
            r = trie[r][ch ^ 1];
        } 
        else r = trie[r][ch];
    }
    return ans;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int q; cin >> q;
    while(q--) {
        char op; 
        int x;
        cin >> op >> x;
        if (op == '+') {
            add(x, 1);
        } else if (op == '-') {
            add(x, -1);
        } else {
            cout << query(x) << "\n";
        }
    }
    return 0;
}
