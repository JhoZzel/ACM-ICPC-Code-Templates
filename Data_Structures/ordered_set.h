#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

template<class T>
using ordered_set = tree<
	T,
	null_type,
	less<T>,
	rb_tree_tag,
	tree_order_statistics_node_update
>;

struct ord_ms {
	int id;
	ordered_set<pair<int,int>> S;
	ord_ms() : id(0) {}
	void insert(int x) { S.insert({x, id++}); }
	int cnt_less(int x) { return S.order_of_key({x, INT_MIN}); }
	int cnt_leq(int x) { return S.order_of_key({x, INT_MAX}); }
	int cnt_grt(int x) { return (int)S.size() - cnt_leq(x); }
	int cnt_geq(int x) { return (int)S.size() - cnt_less(x); }
	int sz() { return S.size(); }
	void clean() {
		id = 0;
		S.clear();
	}
};
