#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;
typedef long long ll;

const int LOG = 60;
const int N = 1e5 + 5;  

struct Trie{ 
    int trie[N * LOG][2];
    int V = 0;    
 
    void add(ll x) { // Insert X in the trie
        int r = 0;
        for (int i = LOG; i >= 0; i--) {
            int ch = (x >> i) & 1;
            if (!trie[r][ch]) trie[r][ch] = ++V;
            r = trie[r][ch];
        }
    }

    ll query(ll x) { // max(X XOR Y) when Y is in the trie
        ll ans = 0;
        int r = 0;
        for (int i = LOG; i >= 0; i--) {
            int ch = (x >> i) & 1;
            if (trie[r][1 - ch]) {
                ans += (1ll << i);
                r = trie[r][1 - ch];
            } 
            else r = trie[r][ch];
        }
        return ans;
    }
};

int main() {
    Trie t;
    t.add(0);
    t.add(5);
    t.add(15);
    t.add(7);
    t.add(1288212);
    t.add(22882191);
    
    ll x;
    while(cin >> x) {
        cout << t.query(x) << endl;
    }
    
    return 0;
}

