#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;

const int MOD = 1e9 + 1;
const int LOG = 30;
const int M = 1e9 + 5;
const int NODES = 5e7;

int q;
int nodes;
int T[NODES], L[NODES], R[NODES], lazy[NODES]; // T guarda el maximo

void create(int &id, int tl, int tr) {
	if (id) return;
	id = ++nodes;
	T[id] = tr;
	lazy[id] = 0;
}

void push(int &id, int tl, int tr) {
	create(id, tl, tr);
	if (lazy[id] == 0) return;
	T[id] += lazy[id];
	if (tl != tr) {
		int tm = (tl + tr) / 2;
		create(L[id], tl, tm);
		create(R[id], tm + 1, tr);
		lazy[L[id]] += lazy[id];
		lazy[R[id]] += lazy[id];
	}
	lazy[id] = 0;
}

int get_first(int k, int &id, int tl, int tr) {
	push(id, tl, tr);
	if (tl == tr) return tl;
	int tm = (tl + tr) / 2;
	push(L[id], tl, tm);
	if (k <= T[L[id]]) return get_first(k, L[id], tl, tm);
	else return get_first(k, R[id], tm + 1, tr);
}

int query(int pos, int &id, int tl, int tr) {
	push(id, tl, tr);
	if (tl == tr) return T[id];
	int tm = (tl + tr) / 2;
	if (pos <= tm) return query(pos, L[id], tl, tm);
	else return query(pos, R[id], tm + 1, tr);
}

void update(int l, int r, int x, int &id, int tl, int tr) {
	push(id, tl, tr);
	if (l > r) return;
	if (tl == l and tr == r) {
		lazy[id] += x;
		push(id, tl, tr);
	} else {
		int tm = (tl + tr) / 2;
		update(l, min(r, tm), x, L[id], tl, tm);
		update(max(tm + 1, l), r, x, R[id], tm + 1, tr);
		T[id] = max(T[L[id]], T[R[id]]);
	}
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int root = 0;
	
	int last = 0;
	cin >> q;
	while(q--) {
		int t; cin >> t;
		int l = get_first(t, root, 0, M);
		int r = get_first(t + 1, root, 0, M); r--;
		update(0, l - 1, +1, root, 0, M);
		update(r + 1, M, -1, root, 0, M);
		
		int k; cin >> k;
		while(k--) {
			int x; cin >> x;
			x = (x + last) % MOD;
			last = query(x, root, 0, M);
			cout << last << "\n";
		}
		assert(nodes < NODES);
	}

	return 0;
}

// https://codeforces.com/contest/1614/problem/E
// https://codeforces.com/blog/entry/156133
