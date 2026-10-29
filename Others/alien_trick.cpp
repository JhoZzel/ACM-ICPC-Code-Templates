#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;
using info = pair<double, int>;

info better(info a, info b) {
	if (abs(a.first - b.first) > 1e-9) return min(a, b);
	return a.second > b.second ? a : b; // tengo la misma rpta pero si voy a tomar segmentos me conviene decirle que por si acaso aun asi 
					    // con esa penalidad puedo yo llegar a tomar todo este rango de segmentos [..  k_opt ,. ..]
					    // el optimo esta en esa misma recta
}

int solve(vector<int> a, int k, int L) {
	reverse(all(a));
	for (int i = 0; i <= L; i++) a.push_back(0);
	reverse(all(a));

	int n = a.size() - 1;

	auto get = [&](double lmb) -> info {
		vector<info> dp(n + 1);
		for (int i = 1; i < L; i++) {
			dp[i] = dp[i - 1];
			dp[i].first += a[i];
		}
		for (int i = L; i <= n; i++) {
			info dp_0 = dp[i - 1];
			dp_0.first += a[i];

			info dp_1 = dp[i - L];
			dp_1.first += lmb;
			dp_1.second += 1;

			dp[i] = better(dp_0, dp_1);
		}
		return dp[n];
	};

	{
		auto [cost, cnt] = get(0);
		if (cnt <= k) {
			return round(cost);
		}
	}

	// lambda -> el precio de tomar 
	int niter = 60;
	double lo = -1e6, hi = 1e6;
	while(niter--) { // 1110000
		double mid = (lo + hi ) / 2;
		if (get(mid).second >= k) lo = mid;  // muy barato el DP esta abusando asi que lo hacemos mas caro el lambda [   |...]
		else hi = mid; // cumple con la restriccion cantidad permitida, pero puede q este muy caro y me limite mucho asi q le bajamso el precio
	}

	auto [cost, cnt] = get(lo);
	int ans = round(cost - k * lo);
	return ans;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	cout << fixed << setprecision(10);

	int n,k,L;
	cin >> n >> k >> L;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		char c; cin >> c;
		a[i] = (bool)islower(c);
	}

	int ans = solve(a, k, L);
	for (int &e : a) e ^= 1;
	ans = min(ans, solve(a, k, L));

	cout << ans << '\n';

	return 0;
}

