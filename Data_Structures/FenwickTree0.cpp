#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define dbg(x) do {cerr << #x <<" = " << (x) << endl; } while (false)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)x.size())
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<pll> vll;

template <class T>
struct FT {
	vector<T> s;

	FT(int n) : s(n) {}
	FT(const vector<int> &A) {
		s.resize(sz(A));
		for (int i = 0; i < sz(A); i++) update(i, A[i]);
	}

	void update(int pos, T x) { // a[pos] += x
		for (; pos < sz(s); pos |= pos + 1)
			s[pos] += x;
	}

	T query(int pos) { // sum of values in [0,pos>
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
		return res;
	}

	T at(int pos) { // a[at]
		return query(pos + 1) - query(pos);
	}

	T query(int l, int r) { // sum of values in [l,r]
		return query(r + 1) - query(l);
	}

	int lower_bound(T sum) { // min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0)
			return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
				pos += pw, sum -= s[pos - 1];
		}
		return pos;
	}
};

int main() {
	vector<int> a({4, 3, 11, 2, 77, 12, 100, 20});
    
	FT<ll> ft(a);
	cout << ft.lower_bound(0) << "\n";
	cout << ft.lower_bound(229) << "\n";
	cout << ft.lower_bound(230) << "\n";

	cout << ft.query(2, 5) << "\n"; // a[2] + a[3] .. + a[5];
	ft.update(3, 100);				// a[3] = 100 => a[3] += 100 => a[3] = 177
	cout << ft.query(2, 5) << "\n"; // a[2] + a[3] .. + a[5];

	return 0;
}
