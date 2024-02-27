#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
using namespace std;

const int N = 1e5 + 5;
const int LOG = 17;

template<class T> 
struct SparseTable { // indexed-0
    T jmp[N][LOG]; // jmp[i][d] = min(a[i], ... a[i + 2^d-1])

    SparseTable(const vector<T>& A) {
        int n = A.size();
        for(int i = 0; i < n; i++) jmp[i][0] = A[i];
        for(int d = 1, p = 1; 2 * p <= n; d++, p <<= 1) {
            for(int i = 0; i + 2 * p - 1 < n; i++) {
                jmp[i][d] = min(jmp[i][d - 1], jmp[i + p][d - 1]);
            }
        }
    }

    T query(int l, int r) { // Consulta indempotente f(A) = f(S(A))
        int d = r - l + 1;
        int k = 31 - __builtin_clz(d); 
        return min(jmp[l][k], jmp[r - (1 << k) + 1][k]);
    }

    T at(int pos) {
        return query(pos, pos);
    }
};

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &e: a) cin >> e;
    int q; cin >> q;
    SparseTable<int> ST(a);
    while(q--) {
        int l,r;
        cin >> l >> r;
        cout << ST.query(l,r) << "\n";
    }
    return 0;
}
