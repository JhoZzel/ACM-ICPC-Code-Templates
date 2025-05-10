#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<int>> jmp;
    
    int f(int a, int b) { return min(a, b); }

    SparseTable(vector<int> &a) {
        const int n = a.size();
        jmp.assign(n + 1, vector<int>(__lg(n) + 1, 0));
        for (int i = 1; i <= n; i++) jmp[i][0] = a[i - 1]; 
        for (int d = 1, p = 1; 2 * p <= n; d++, p <<= 1) {
            for (int i = 1; i + 2 * p - 1 <= n; i++) {
                jmp[i][d] = f(jmp[i][d - 1], jmp[i + p][d - 1]);
            }
        }
    }

    int query(int l, int r) { // 0-indexed
        l++; r++; 
        int d = r - l + 1; 
        int k = __lg(d);
        return f(jmp[l][k], jmp[r - (1 << k) + 1][k]);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &e : a) cin >> e;

    SparseTable st(a);
    for (int i = 0; i < q; i++) {
        int l,r;
        cin >> l >> r;
        l--; r--;
        cout << st.query(l, r) << "\n";
    }

    return 0;
}
