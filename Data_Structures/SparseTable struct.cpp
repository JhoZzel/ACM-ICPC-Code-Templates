// Sparse Table
//

struct SparseTable {
    int f(int a, int b) { return min(a, b); }
    
    vector<vector<int>> st;

    SparseTable(vector<int> &a) { // 0-indexed
        int n = a.size();
        int k = __lg(n) + 1;
        st.resize(n, vector<int>(k));
        for (int i = 0; i < n; i++) st[i][0] = a[i];
        for (int p = 1, d = 1; 2 * d <= n; p++, d <<= 1) {
            for (int i = 0; i + 2 * d <= n; i++) {
                st[i][p] = f(st[i][p - 1], st[i + d][p - 1]);
            }
        }
    }
    
    int query(int l, int r) {
        int k = __lg(r - l + 1);
        int d = (1 << k);
        return f(st[l][k], st[r - d + 1][k]);
    }

    /*int query(int l, int r) {
        int len = r - l + 1;
        int mn = INT_MAX;
        while(len) {
            int k = __lg(len);
            mn = f(mn, st[l][k]);
            l += (1 << k);
            len ^= (1 << k);
        }
        return mn;
    }*/
};
