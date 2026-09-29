#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

const int N = 1e5 + 5;
const int LOG = 20; 
const int NODES = LOG * N;

int n,m,q;
int nodes;
int a[N];
int root[N];
int L[NODES];
int R[NODES];
int T[NODES];

int copy(int old) {
	int cur = ++nodes;
	T[cur] = T[old];
	L[cur] = L[old];
	R[cur] = R[old];
	return cur;
}

int update(int old, int pos, int x, int tl = 0, int tr = m - 1) {  // 0 indexed histogram
	int cur = copy(old);
	if (tl == tr) {
		T[cur] += x;
	} else {
		int tm = (tl + tr) / 2;
		if (pos <= tm) L[cur] = update(L[cur], pos, x, tl, tm);
		else R[cur] = update(R[cur], pos, x, tm + 1, tr);
		T[cur] = T[L[cur]] + T[R[cur]];
	}
	return cur;
}

int query(int l_id, int r_id, int k, int tl = 0, int tr = m - 1) { // kth smallest 1-indexed
	if (tl == tr) return tl; // k >= 1
	int tm = (tl + tr) / 2;
	int freq = T[L[r_id]] - T[L[l_id]];
	if (k <= freq) return query(L[l_id], L[r_id], k, tl, tm);
	return query(R[l_id], R[r_id], k - freq, tm + 1, tr);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;

	vector<int> t;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		t.push_back(a[i]);
	}

	sort(all(t));
	t.erase(unique(all(t)), t.end());
	m = t.size(); // number of different elements

	// building versions of ST
	root[0] = 0; // vacio redirige a si mismo
	for (int i = 1; i <= n; i++) { // 1-indexed
		int pos = lower_bound(all(t), a[i]) - t.begin();
		root[i] = update(root[i - 1], pos, 1);
	}

	while(q--) {
		int l,r,k;
		cin >> l >> r >> k;
		int j = query(root[l - 1], root[r], k);
		cout << t[j] << '\n';
	}

	return 0;
}
