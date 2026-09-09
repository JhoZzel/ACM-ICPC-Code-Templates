#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int N = 1000 + 5;
const int M = 100 + 5;

ll dp[N][M][2];

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

	int n;
	string t;
	cin >> n >> t;
	
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


	// Number of strings of length n having a given pattern of length m as their substring
	dp[0][0][0] = 1;
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j <= m; j++) {
			for (int c = 0; c < 26; c++) {
				int to = aut[j][c];
				for (int b : {0, 1}) {
					int nb = b or (to == m);
					dp[i + 1][to][nb] += dp[i][j][b];
					dp[i + 1][to][nb] %= MOD;
				}
			}
		}
	}

	ll ans = 0;
	for (int j = 0; j <= m; j++) ans += dp[n][j][1];
	ans %= MOD;
	
	cout << ans << "\n";

	return 0;
}

// https://cses.fi/problemset/task/1112/
