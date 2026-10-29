// LIS
//

int LIS(vector<int> &a) { 
	int n = a.size();
	vector<int> d(n + 1, INF);
	d[0] = -INF;
	int lis = 0;
	for (int x : a) {
		int j = lower_bound(all(d), x) - d.begin(); // strict <
		//int j = upper_bound(all(d), x) - d.begin(); // <=
		d[j] = x;
		lis = max(lis, j);
	}
	return lis;
}
