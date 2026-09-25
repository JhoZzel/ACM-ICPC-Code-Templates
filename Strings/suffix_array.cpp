// Suffix Array
//

#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const int N = 2e5 + 5;
const int LOG = 20;

int st[N][LOG];

void build(vector<int> &a) {
	int n = sz(a);
	for (int i = 0; i < n; i++) st[i][0] = a[i];
	for (int j = 1, d = 1; 2 * d <= n; d <<= 1, j++) {
		for (int i = 0; i + 2 * d <= n; i++) {
			st[i][j] = min(st[i][j - 1], st[i + d][j - 1]);
		}
	}
}

int query(int l, int r) {
	if (l > r) swap(l, r);
	if (l == r) return 0; // may be return INT_MAX can be useful
	r--;
	int k = __lg(r - l + 1);
	int d = (1 << k);
	return min(st[l][k], st[r - d + 1][k]);
}

// LCP between suf[i] and suf[i + 1]    suf[n - 1] = 0;
vector<int> lcp_array(string &s, vector<int> &suf) {
	int n = sz(s);
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
	int n = sz(s);
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

int cnt_str(string &s, vector<int> &suf, string &p) { // online queries patterns matching
	if (sz(p) > sz(s)) return 0;
	auto L = lower_bound(suf.begin() + 1, suf.end(), p, [&](int id, const string& pat) {
		return s.compare(id, sz(pat), pat) < 0;
	});
	auto R = upper_bound(suf.begin() + 1, suf.end(), p, [&](const string& pat, int id) {
		return s.compare(id, sz(pat), pat) > 0;
	});
	return R - L;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string s; cin >> s; 
	s += "$";

	int n = s.size();
	vector<int> suf = suffix_array(s);
	vector<int> lcp = lcp_array(s, suf);
	build(lcp);
	vector<int> pos(n);
	for (int i = 0; i < n; i++) pos[suf[i]] = i;

	cout << "s: " << s << endl;
	cout << "pos: ";
	for (int i = 0; i < n; i++) cout << pos[i] << " ";
	cout << '\n';

	return 0;
}
