#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1000 + 5;
const int MAX = 1e6 + 6;
const int MOD = 1e9 + 7;

ll F[MAX], Fi[MAX], B[N];

ll bpow(ll a, ll e) {
	ll r = 1;
	while (e) {
		if (e & 1) r = r * a % MOD;
		a = a * a % MOD;
		e >>= 1;
	}
	return r;
}

ll comb(int n, int k) {
	if (k < 0 or k > n) return 0;
	return F[n] * Fi[k] % MOD * Fi[n - k] % MOD;
}


// Faulhaber's Formula  S = 1^p + 2^p + ... + n^p 
ll sum(ll n, int p) { 
	n %= MOD;
	ll sa = 0, pw = n;
	for (int j = p; j >= 0; j--) {
		sa += (j & 1 ? -1 : 1) * comb(p + 1, j) * B[j] % MOD * pw % MOD;
		sa %= MOD;
		pw = pw * n % MOD;
	}
	sa = sa * bpow(p + 1, MOD - 2) % MOD;
	if (sa < 0) sa += MOD;

	return sa;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	F[0] = 1;
	for (int i = 1; i < MAX; i++) F[i] = i * F[i - 1] % MOD;
	Fi[MAX - 1] = bpow(F[MAX - 1], MOD - 2);
	for (int i = MAX - 2; i >= 0; i--) Fi[i] = (i + 1) * Fi[i + 1] % MOD;
	assert(Fi[0] == 1);

	// B[0] = 1, B[1] = -1/2
	B[0] = 1; 
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < i; j++) {
			B[i] += comb(i + 1, j) * B[j] % MOD;
			B[i] %= MOD;
		}
		B[i] = -B[i] * bpow(i + 1, MOD - 2) % MOD;
		if (B[i] < 0) B[i] += MOD;
	}

	return 0;
}
