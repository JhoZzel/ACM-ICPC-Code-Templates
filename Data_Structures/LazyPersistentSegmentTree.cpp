#include <bits/stdc++.h>
using namespace std;

const int Q = 1e5 + 5;
const int NODES = 2e7;;

int n,m,M,q;
int nodes;
int T[NODES];
int L[NODES];
int R[NODES];
int root[Q];
int lazy[NODES];

int copy(int old) {
	int cur = nodes++;
	L[cur] = L[old];
	R[cur] = R[old];
	T[cur] = T[old];
	lazy[cur] = lazy[old];
	return cur;
}

int push(int old, int tl, int tr) {
	int cur = copy(old);
	if (lazy[cur] == 0) return cur;
	int len = (tr - tl +1);
	T[cur] = len - T[cur];
	if (tl != tr) {
		L[cur] = copy(L[old]);
		R[cur] = copy(R[old]);
		lazy[L[cur]] ^= lazy[cur];
		lazy[R[cur]] ^= lazy[cur];
	}
	lazy[cur] = 0;
	return cur;
}

int update_range(int old, int l, int r, int tl = 0, int tr = M - 1) {
	int cur = push(old, tl, tr);
	if (l > r) return cur;
	if (tl == l and tr == r)  {
		lazy[cur] ^= 1;
		cur = push(cur, tl, tr);
	} else {
		int tm = (tl + tr) / 2;
		L[cur] = update_range(L[cur], l, min(tm, r), tl, tm);
		R[cur] = update_range(R[cur], max(tm + 1, l), r, tm + 1, tr);
		T[cur] = T[L[cur]] +  T[R[cur]];
	}
	return cur;
}

int update(int old, int pos, int x, int tl = 0, int tr = M - 1) {
	int cur = push(old, tl, tr);
	if (tl == tr) {
		T[cur] = x;
	} else {
		int tm = (tl + tr) / 2;
		if (pos <= tm) {
			L[cur] = update(L[cur], pos, x, tl, tm);
			R[cur] = push(R[cur], tm + 1, tr);
		} else {
			R[cur] = update(R[cur], pos, x, tm + 1, tr);
			L[cur] = push(L[cur],tl, tm);
		}
		T[cur] = T[L[cur]] + T[R[cur]];
	}
	return cur;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	cin >> n >> m >> q;
	root[0] = nodes++;
	M = n * m;
	for (int rt = 1; rt <= q; rt++) {
		int op; cin >> op;
		if (op == 1) {
			int i,j;
			cin >> i >> j;
			i--; j--;
			int pos = i * m + j;
			root[rt] = update(root[rt - 1], pos, 1);
		} else if (op == 2){
			int i,j;
			cin >> i >> j;
			i--; j--;
			int pos = i * m + j;
			root[rt] = update(root[rt - 1], pos, 0);
		} else if (op == 3){
			int i; cin >> i;
			i--;
			int l = i * m, r = (i + 1) * m - 1;
			root[rt] = update_range(root[rt - 1], l, r); // flip
		} else {
			int k; cin >> k;
			root[rt] = root[k];
		}
		cout << T[root[rt]] << "\n";
	}

	return 0;
}
// https://codeforces.com/group/9ksB4OUCbY/contest/704950/problem/B
