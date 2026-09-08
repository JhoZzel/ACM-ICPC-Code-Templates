#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()

using ll = long long;

vector<int> kmp(string s) {
	int n = s.size();
	vector<int> p(n);
	for (int i = 1; i < n; i++) {
		int j = p[i - 1];
		while(j and s[j] != s[i]) j = p[j - 1];
		if (s[i] == s[j]) j++;
		p[i] = j;
	}
	return p;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	string s,t;
	cin >> s >> t;
	
	int n = s.size();
	int m = t.size();

	vector<int> p = kmp(t);

	t += " ";

	// compute automaton
	vector aut(m + 1, vector(26, 0));
	for (int i = 0; i <= m; i++) {
		for (int c = 0; c < 26; c++) {
			char now = 'a' + c;
			if (i and now != t[i]) aut[i][c] = aut[p[i - 1]][c];
			else aut[i][c] = i + (now == t[i]);
		}
	}

	vector dp(n + 1, vector(m + 1, -1));
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			if (dp[i][j] == -1) continue;
			int lo = 0, hi = 25;
			if (s[i] != '?') lo = hi = s[i] - 'a';
			for (int c = lo; c <= hi; c++) {
				int k = aut[j][c];
				dp[i + 1][k] = max(dp[i + 1][k], dp[i][j] + (k == m));
			}
		}
	}

	int ans = 0;
	for (int j = 0; j <= m; j++) ans = max(ans, dp[n][j]);
	cout << ans << "\n";

	return 0;
}

