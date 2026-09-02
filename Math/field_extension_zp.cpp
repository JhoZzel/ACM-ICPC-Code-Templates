#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int OMG = 5; // We are working in Z[sqrt(5)]    w := omega

struct Num {
	ll x, y; // Represents x + y * sqrt(OMG)

	Num(ll _x = 0, ll _y = 0) {
		x = _x % MOD;
		y = _y % MOD;
		if (x < 0) x += MOD;
		if (y < 0) y += MOD;
	}

	Num operator + (const Num &other) const {
		return Num(x + other.x, y + other.y);
	}

	Num operator - (const Num &other) const {
		return Num(x - other.x, y - other.y);
	}

	Num operator * (const Num &other) const {
		ll nx = (x * other.x + y * other.y % MOD * OMG) % MOD;
		ll ny = (x * other.y + y * other.x) % MOD;
		return Num(nx, ny);
	}
};

ll bpow(ll a, ll e) {
	ll r = 1;
	while(e) {
		if (e & 1) r = r * a % MOD;
		a = a * a % MOD;
		e >>= 1;
	}
	return r;
}

ll inv(ll a) {
	return bpow(a, MOD - 2);
}

// Inverse of a field element
// 1 / (x + y*sq) = (x - y*sq) / (x^2 - w*y^2)
Num inv(Num n) {
	ll nn = (n.x * n.x - n.y * n.y % MOD * OMG) % MOD; // algebraic norm
	if (nn < 0) nn += MOD;
	ll invn = inv(nn);
	// Result is (x * inv_norm) - (y * inv_norm) * sqrt(w)
	return Num(n.x * invn % MOD, (MOD - n.y) * invn % MOD);
}

Num bpow(Num a, ll e) {
	Num r(1, 0); // Result starts as 1 + 0*sqrt(5)
	while (e) {
		if (e & 1) r = r * a;
		a = a * a;
		e >>= 1;
	}
	return r;
}

const int INV2 = inv(2);
const int INV5 = inv(5);

const Num phi = Num(INV2, INV2);
const Num psi = Num(INV2, -INV2);

// Binet's formula: f_n = 1/sqrt(5) x ( phi ^ n - psi ^ n )

ll fibo(ll n) {
	Num e1 = bpow(phi, n), e2 = bpow(psi, n);
	Num k(0, INV5);
	Num res = (e1 - e2) * k;
	assert(res.y == 0);
	return res.x;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	Num xd;
	
	for (int i = 1; i <= 100; i++) {
		cout << fibo(i) << endl;
	}
	return 0;
}
