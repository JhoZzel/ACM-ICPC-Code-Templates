#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;

int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return 1ll * a * b % MOD; }
int bpow(int a, int e) {
    int r = 1;
    while(e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}

int n,m;
vector<vector<int>> a;

void pv() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void transpose(vector<vector<int>> &a) {
    vector b(m, vector(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            b[j][i] = a[i][j];

    swap(a, b);
    swap(n, m);
}


int main() {
	cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> m;
    a.assign(n, vector(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    if (n == 0 or m == 0) {
        cout << "0\n";
        return 0;
    }

    if (m > n) transpose(a);

    int r = 0;
    for (int j = 0; j < m; j++) {
        int p = -1;
        for (int i = r; i < n; i++) {
            if (a[i][j]) p = i;
        }
        if (p == -1) continue;
        swap(a[r], a[p]);
        int inv = bpow(a[r][j], MOD - 2);
        for (int k = j; k < m; k++) {
            a[r][k] = mul(a[r][k], inv);
        }
        for (int i = r + 1; i < n; i++) {
            int f = a[i][j];
            for (int k = j; k < m; k++) {
                a[i][k] = add(a[i][k], MOD - mul(a[r][k], f));
            }
        }
        r++;
        if (r == n) break;
    }
    cout << r << '\n';

	return 0;
}
