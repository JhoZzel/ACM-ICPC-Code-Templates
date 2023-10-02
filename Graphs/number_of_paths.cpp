#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int MOD = 1e9 + 7;

/*
 Given an adjacency matrix of a directed graph with n
 nodes, compute the number of paths from node 1
 to node n with length exactly L

 You must consider all paths, so repeating nodes is valid for each path.
 
 Time Complexity: O(log k n^3)
 */

vvi get_adj_matrix(int n) {
    vvi ady(n,vi(n));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> ady[i][j];
        }
    }
    return ady;
}

vvi ident_matrix(int n) {
    vvi id(n,vi(n,0));
    for (int i=0; i<n; i++) id[i][i] = 1;
    return id;
}

vvi mul_matrix(vvi &A, vvi &B, int n) { 
    vvi res(n, vi(n,0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                res[i][j] = (res[i][j] + 1ll * A[i][k] * B[k][j] % MOD) % MOD;
            }
        }
    }
    return res;
}

vvi bin_power_matrix(vvi &ady, int e, int n) {
    vvi res = ident_matrix(n); 
    while(e) {
        if (e & 1) res = mul_matrix(res, ady, n);
        ady = mul_matrix(ady, ady, n);
        e >>= 1;
    }
    return res;
}

int main() {
    int n,l;
    cin >> n >> l;
    vvi ady = get_adj_matrix(n);
    ady = bin_power_matrix(ady,l,n);
    cout << ady[0][n-1] << "\n";
    return 0;
}
