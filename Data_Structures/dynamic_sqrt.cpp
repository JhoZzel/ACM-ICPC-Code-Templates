#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;

struct Block {
	vector<int> v, ord;	
	Block() {}
	Block(vector<int> &v) : v(v), ord(v) {
		sort(all(ord));
	}
	void add(int i, int x) {
		v.insert(v.begin() + i, x);
		auto it = lower_bound(all(ord), x);
		ord.insert(it, x);
	}
	int remove(int i) {
		auto it = lower_bound(all(ord), v[i]);
		int val = *it;
		assert(val == v[i]);
		ord.erase(it);
		v.erase(v.begin() + i);
		return val;
	}
	int cnt_leq(int x) {
		return upper_bound(all(ord), x) - ord.begin();
	}
	int cnt() {
		return sz(v);
	}
};


const int B = 634; // 2 sqrt(N)

vector<Block> big;

void rebuild() {
	vector<int> a;
	for (Block &b : big) a.insert(a.end(), all(b.v));
	vector<Block> res;
	vector<int> bucket;
	for (int x : a) {
		bucket.emplace_back(x);
		if (sz(bucket) > B) {
			res.emplace_back(bucket);
			bucket.clear();
		}
	}
	res.emplace_back(bucket);
	swap(big, res);
}

void add(int i, int x) {
	for (Block &b : big) {
		if (i <= b.cnt()) {
			b.add(i, x);
			break;
		}
		i -= b.cnt();
	}
}

int remove(int i) {
	for (Block &b : big) {
		if (i < b.cnt()) {
			return b.remove(i);
		} 
		i -= b.cnt();
	}
	assert(false);
	return -1;
}

int sum(int k, int x) {
	int cnt = 0;
	for (Block &b : big) {
		if (k > b.cnt()) {
			k -= b.cnt();
			cnt += b.cnt_leq(x);
		} else {
			for (int val : b.v) {
				if (k == 0) break;
				k -= 1;
				cnt += val <= x;
			}
			break;
		}
	}
	return cnt;
}

int get(int k, int x) {
	return sum(k, x) - sum(k, x - 1);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	
	int n; cin >> n;
	vector<int> a(n);
	for (int &e : a) cin >> e;
	
	big.emplace_back(a);

	rebuild();

	int q; cin >> q;
	int last = 0;
	
	auto decode = [&]() {
		int x; cin >> x;
		x += last - 1;
		x %= n;
		if (x < 0) x += n;
		x += 1;
		return x;
	};

	int cnt = 0;
	while(q--) {
		int op; cin >> op;
		if (op == 1) {
			int l = decode();
			int r = decode();
			l--; r--;
			if (l > r) swap(l, r);
			int val = remove(r);
			add(l, val);
		} else {
			int l = decode();
			int r = decode();
			int k = decode();
			if (l > r) swap(l, r);
			last = get(r, k) - get(l - 1, k);
			cout << last << "\n";
		}

		cnt++;
		if (cnt > B) {
			rebuild();
			cnt = 0;
		}
	}

	return 0;
}

// https://codeforces.com/problemset/problem/455/D
