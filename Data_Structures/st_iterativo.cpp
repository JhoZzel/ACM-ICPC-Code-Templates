struct node {
	ll mn;
	node() : mn(INF) {}
	node(ll x) : mn(x) {}
	node operator + (node &other) {
		node q;
		q.mn = min(mn, other.mn);
		return q;
	}
};
 
template<typename T>
struct SegmentTree {
	int N;
	vector<T> ST;
 
	SegmentTree(int n) {
		N = 1;
		while (N < n) N <<= 1;
		ST.assign(N << 1, T());
	}
	void update(int i, T val){
		ST[i += N] = val;
		while(i >>= 1)
			ST[i] = ST[i << 1] + ST[i << 1 | 1];
	}
 
	T query(int l, int r){
		T resL = T(), resR = T(); 
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) resL = resL + ST[l++];
			if(!(r & 1)) resR = ST[r--] + resR;
		}
		return resL + resR;
	}
};
