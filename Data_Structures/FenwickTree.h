struct FenwickTree { // 0-indexed    [0, n - 1]
	int n;
	vector<ll> FT;
	FenwickTree(int n) : n(n), FT(n + 1, 0) {}
	void update(int i, ll x) {
		for (++i; i <= n; i += i & -i) FT[i] += x;
	}
	ll sum(int i) { 
		if (i >= n) i = n - 1; // out of range
		ll sa = 0;
		for (++i; i > 0; i -= i & -i) sa += FT[i];
		return sa;
	}
	ll query(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};
