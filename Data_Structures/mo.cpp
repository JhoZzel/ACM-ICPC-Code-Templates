// Mo Algorithm
//

#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

using ll = long long;

const int N = 1e5 + 5;
const int B = 317;

struct Query {
	int l, r, idx;
	bool operator < (const Query other) const {
		int block_a = l / B, block_b = other.l / B;
		if (block_a != block_b) return block_a < block_b;
		return ((block_a & 1) ? (r > other.r) : (r < other.r)); 
	}
};

void update(int x, int del) {
	
}

ll get_answer() {
	
}


vector<int> mo_algorithm(vector<Query> Q) {
	vector<int> ans(sz(Q));
	sort(all(Q));
	int cur_l = 0, cur_r = -1; // 0-indexed
	for (Query q : Q) {
		while (cur_l > q.l) {
			update(--cur_l, 1);
		}
		while (cur_r < q.r) {
			update(++cur_r, 1);
		}
		while (cur_l < q.l) {
			update(cur_l++, -1);
		}
		while (cur_r > q.r) {
			update(cur_r--, -1);
		}
		ans[q.idx] = get_answer();
	}
	return ans;
}

vector<int> mo_algorithm(vector<Query> Q) {
	vector<int> ans(sz(Q));
	sort(all(Q));
	int cur_l = 0, cur_r = -1; // 0-indexed
	for (Query q : Q) {
		while (cur_l > q.l) {
			cur_l--;
			add(cur_l);
		}
		while (cur_r < q.r) {
			cur_r++;
			add(cur_r);
		}
		while (cur_l < q.l) {
			remove(cur_l);
			cur_l++;
		}
		while (cur_r > q.r) {
			remove(cur_r);
			cur_r--;
		}
		ans[q.idx] = get_answer();
	}
	return ans;
}
