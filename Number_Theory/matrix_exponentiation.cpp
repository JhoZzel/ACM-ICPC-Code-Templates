#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

vvl read_matrix() {
    int r,c; cin >> r >> c;
    vvl A(r,vl(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> A[i][j];
        }
    }
    return A;
}

void print_matrix(vvl &A) {
    for (vl v : A) {
        for (ll e : v) {
            cout << e << " ";
        }
        cout << "\n";
    }
}

vvl ident_matrix(int n) {
    vvl id(n,vl(n,0));
    for (int i=0; i<n; i++) id[i][i] = 1;
    return id;
}

vvl add_matrix(vvl &A, vvl &B) {
    int ra = A.size(), ca = A[0].size();
    int rb = B.size(), cb = B[0].size();
    assert(ra == rb and ca == cb);
    vvl C(ra,vl(cb,0));
    for (int i = 0; i < ra; ++i) {
        for (int j = 0; j < cb; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vvl mul_matrix(vvl &A, vvl &B) {
    int ra = A.size(), ca = A[0].size();
    int rb = B.size(), cb = B[0].size();
    if (ca != rb) cout << ">o<\n";
    vvl C(ra,vl(cb,0));
    for (int i = 0; i < ra; ++i) {
        for (int j = 0; j < cb; ++j) {
            for (int k = 0; k < ca; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vvl bin_power_matrix(vvl &M, int e) { 
    int n = M.size();
    vvl res = ident_matrix(n); 
    while(e) {
        if (e & 1) res = mul_matrix(res, M);
        M = mul_matrix(M, M);
        e >>= 1;
    }
    return res;
}

int main() {
    vvl A = read_matrix();
    vvl B = read_matrix();
    vvl C = add_matrix(A,B);
    print_matrix(C);
    return 0;
}
