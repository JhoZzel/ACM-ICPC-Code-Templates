#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;
using ull = unsigned long long;

ull mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull bpow(ull a, ull e, ull mod) {
	ull r = 1;
    for (; e; a = mul(a, a, mod), e >>= 1) {
        if (e & 1) r = mul(r, a, mod);
    }
	return r;
}

bool is_prime(ull n) {
	if (n < 2 or n % 6 % 4 != 1) return n - 2 < 2;
	ull s = __builtin_ctzll(n - 1), d = n >> s;
	for (ull a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		ull p = bpow(a % n, d, n), i = s;
		while(p != 1 and p != n - 1 and a % n and i--) p = mul(p, p, n);
		if (p != n - 1 and i != s) return 0;
	}
	return 1;
}
ull pollard(ull n) {
	auto f = [n](ull x) { return mul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while(t++ % 40 or (gcd(prd, n) == 1)) {
		if (x == y) x = ++i, y = f(x);
		if ((q = mul(prd, max(x, y) - min(x, y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return gcd(prd, n);
}

vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (is_prime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}

vector<ull> divisors(ull n) {
	vector<ull> pr = factor(n);
    sort(all(pr));
    vector<ull> D = {1};
    for (int i = 0; i < sz(pr); ) {
        int j = i;
        while(j < sz(pr) and pr[i] == pr[j]) j++;
        int k = j - i;
        i = j;
        int cur = sz(D);
        ll pw = 1;
        for (int x = 1; x <= k; x++) {
            pw *= pr[i - 1];
            for (int u = 0; u < cur; u++) D.push_back(D[u] * pw); 
        }
    }
    return D;
}

int main() {
    ull n;
	while(cin >> n) {
		vector<ull> D = divisors(n);
        cout << "n = " << n << '\n';
        for (auto d : D) cout << d << " ";
        cout << '\n';
	}
	return 0;
}
