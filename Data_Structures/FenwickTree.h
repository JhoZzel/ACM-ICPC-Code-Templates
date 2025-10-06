struct FenwickTree { // 0-indexed
    int N;
    vector<int> FT;
    FenwickTree(int n): N(n + 5), FT(n + 5) {}
    void update(int i, int x) {
        for (++i; i < N; i += i & -i) FT[i] += x;
    }
    int sum(int i) {
        int sa = 0;
        for (++i; i > 0; i -= i & -i) sa += FT[i];
        return sa;
    }
    int query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

