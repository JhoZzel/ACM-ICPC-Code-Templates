// Suffix Array
//

#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

const int N = 2e5 + 5;
const int LOG = 20;

int st[N][LOG];

void build(vector<int> &a) {
    const int n = a.size();
    for (int i = 0; i < n; i++) st[i][0] = a[i];
    for (int j = 1, d = 1; 2 * d <= n; d <<= 1, j++) {
        for (int i = 0; i + 2 * d <= n; i++) {
            st[i][j] = min(st[i][j - 1], st[i + d][j - 1]);
        }
    }
}

int query(int l, int r) {
    if (l > r) swap(l, r);
    if (l == r) return 0;
    r--;
    int k = __lg(r - l + 1);
    int d = (1 << k);
    return min(st[l][k], st[r - d + 1][k]);
}

// LCP between suf[i] and suf[i + 1]    suf[n - 1] = 0;
vector<int> lcp_array(string &s, vector<int> &suf) {
    const int n = s.size();
    vector<int> r(n);
    for (int i = 0; i < n; i++) r[suf[i]] = i;
    int k = 0;
    vector<int> lcp(n);
    for (int i = 0; i < n; i++) {
        if (r[i] + 1 == n) {
            k = 0;
            continue;
        }
        int j = suf[r[i] + 1];
        while(i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
        lcp[r[i]] = k;
        if (k) k--;
    }
    return lcp;
}

// We have to add $ at the final of s
vector<int> suffix_array(string &s) {
    const int n = s.size();
    vector<int> a(n), c(n);
    iota(all(a), 0);
    sort(all(a), [&](int i, int j) {
        return s[i] < s[j];
    });
    c[a[0]] = 0;
    for (int i = 1; i < n; i++) {
        c[a[i]] = c[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
    }
    int len = 1;
    vector<int> h(n), nc(n), sbs(n);
    while(len < n) {
        for (int i = 0; i < n; i++) sbs[i] = (a[i] - len + n) % n;
        for (int i = n - 1; i >= 0; i--) h[c[a[i]]] = i;
        for (int i = 0; i < n; i++) {
            int x = sbs[i];
            a[h[c[x]]++] = x;
        }
        nc[a[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (c[a[i - 1]] != c[a[i]]) nc[a[i]] = nc[a[i - 1]] + 1;
            else {
                int pre = c[(a[i - 1] + len) % n];
                int cur = c[(a[i] + len) % n];
                nc[a[i]] = nc[a[i - 1]] + (pre != cur);
            }
        }
        swap(c, nc);
        len <<= 1;
    }
    return a;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    string s; cin >> s;
    s += "$";
    int n = s.size();
    vector<int> suf = suffix_array(s);
    vector<int> lcp = lcp_array(s, suf);
    build(lcp);
    vector<int> r(n);
    for (int i = 0; i < n; i++) r[suf[i]] = i;
    cout << "s: " << s << endl;
    cout << "r: ";
    for (int i = 0; i < n; i++) cout << r[i] << " ";
    cout << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cout << i << ", " << j << " -> " << query(i, j) << '\n';
        }
    }
    return 0;
}


