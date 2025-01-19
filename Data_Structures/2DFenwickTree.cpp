#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;

int n,q;
int FT[N][N];

void update(int x, int y, int d) {
    for (int i = x; i < N; i += i & -i) 
        for (int j = y; j < N; j += j & -j) 
            FT[i][j] += d;
}

int sum(int x, int y) {
    int sa = 0;
    for (int i = x; i; i -= i & -i) 
        for (int j = y; j; j -= j & -j)
            sa += FT[i][j];
    return sa;
}

int query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
}


int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            if (c == '*') update(i, j, 1);
        }
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i,j;
            cin >> i >> j;
            int at = query(i, j, i, j);
            update(i, j, at ? -1 : 1);
        } else {
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query(x1, y1, x2, y2) << '\n';
        }       
    }

    return 0;
}
