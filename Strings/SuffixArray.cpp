#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

// LCP between suf[i] and suf[i + 1]    suf[n] = 0
vector<int> lcp_array(string &s, vector<int> &suf) { 
	const int n = s.size();
	vector<int> rank(n);
	for(int i = 0; i < n; i++) rank[suf[i]] = i;
	int k = 0;
	vector<int> lcp(n);
	for (int i = 0; i < n; i++){
		if (rank[i] + 1 == n){
			k = 0;
			continue;
		}
		int j = suf[rank[i] + 1];
		while (i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
		lcp[rank[i]] = k;
        if (k) k--;
	}
	return lcp;
}

vector<int> suffix_array(string &s) {
	const int n = s.size();
	vector<int> a(n); 
	vector<int> c(n);
	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [&] (int i, int j){
		return s[i] < s[j];
	});

	c[a[0]] = 0;
	for (int i = 1; i < n; i++){
	    c[a[i]] = c[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
	}

	int len = 1;
	vector<int> head(n);
	vector<int> nc(n);
	vector<int> sbs(n);
	
    while (len < n){
		for (int i = 0; i < n; i++) sbs[i] = (a[i] - len + n) % n;
		for (int i = n - 1; i >= 0; i--) head[c[a[i]]] = i;
		for (int i = 0; i < n; i++){
			int x = sbs[i];
			a[head[c[x]]++] = x;
		}
		nc[a[0]] = 0;
		for (int i = 1; i < n; i++){
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
    string s; cin >> s; s += "$";
    int n = s.size() - 1;
    vector<int> suf = suffix_array(s);
    vector<int> lcp = lcp_array(s, suf);

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += n - suf[i] - lcp[i - 1];
    }
    cout << ans << "\n";

    return 0;
}
// https://cses.fi/problemset/task/2105
