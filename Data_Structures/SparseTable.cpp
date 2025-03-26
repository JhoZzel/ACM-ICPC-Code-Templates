#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int LOG = 20;

int n,q;
int a[N];
int jmp[N][LOG];

int f(int a, int b) {
    return min(a, b);
}

void build() { // 1-indexed
    for (int i = 1; i <= n; i++) jmp[i][0] = a[i];
    for (int d = 1, p = 1; 2 * p <= n; d++, p <<= 1) {
        for (int i = 1; i + 2 * p - 1 <= n; i++) {
            jmp[i][d] = f(jmp[i][d - 1], jmp[i + p][d - 1]);
        }
    }
}

int query(int l, int r) { // f(A) = f(S(A)) 
    int d = r - l + 1; 
    int k = __lg(d);
    return f(jmp[l][k], jmp[r - (1 << k) + 1][k]);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    cin >> q;
    while(q--) {
        int l,r;
        cin >> l >> r;
        l++; r++;
        if (l > r) swap(l, r);
        cout << query(l, r) << '\n';
    }
    return 0;
}
