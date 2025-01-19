#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;

int n,q;
bool a[N][N];
int T[4 * N][4 * N];

void build_y(int id_x, int tl_x, int tr_x, int id_y = 1, int tl_y = 1, int tr_y = n) {
    if (tl_y == tr_y) {
        if (tl_x == tr_x)
            T[id_x][id_y] = a[tl_x][tl_y];
        else
            T[id_x][id_y] = T[2 * id_x][id_y] + T[2 * id_x + 1][id_y];
    } else {
        int tm_y = (tl_y + tr_y) / 2;

        build_y(id_x, tl_x, tr_x, 2 * id_y, tl_y, tm_y);
        build_y(id_x, tl_x, tr_x, 2 * id_y + 1, tm_y + 1, tr_y);
        
        T[id_x][id_y] = T[id_x][2 * id_y] + T[id_x][2 * id_y + 1];
    }
}

void build_x(int id_x = 1, int tl_x = 1, int tr_x = n) { 
    if (tl_x != tr_x) {
        int tm_x = (tl_x + tr_x) / 2;
        build_x(2 * id_x, tl_x, tm_x);
        build_x(2 * id_x + 1, tm_x + 1, tr_x);
    }
    build_y(id_x, tl_x, tr_x);
}

int query_y(int ly, int ry, int id_x, int id_y = 1, int tl_y = 1, int tr_y = n) {
    if (ly > ry) return 0;
    if (ly == tl_y and tr_y == ry) return T[id_x][id_y];
    int tm_y = (tl_y + tr_y) / 2;
    int valL = query_y(ly, min(tm_y, ry), id_x, 2 * id_y, tl_y, tm_y);
    int valR = query_y(max(tm_y + 1, ly), ry, id_x, 2 * id_y + 1, tm_y + 1, tr_y);
    return valL + valR;
}

int query_x(int lx, int rx, int ly, int ry, int id_x = 1, int tl_x = 1, int tr_x = n) {
    if (lx > rx) return 0;
    if (lx == tl_x and tr_x == rx) return query_y(ly, ry, id_x);
    int tm_x = (tl_x + tr_x) / 2;
    int valL = query_x(lx, min(tm_x, rx), ly, ry, 2 * id_x, tl_x, tm_x);
    int valR = query_x(max(tm_x + 1, lx), rx, ly, ry, 2 * id_x + 1, tm_x + 1, tr_x);
    return valL + valR;
}

void update_y(int x, int y, int id_x, int tl_x, int tr_x, int id_y = 1, int tl_y = 1, int tr_y = n) {
    if (tl_y == tr_y) {
        if (tl_x == tr_x)
            T[id_x][id_y] ^= 1;
        else
            T[id_x][id_y] = T[2 * id_x][id_y] + T[2 * id_x + 1][id_y];
    } else {
        int tm_y = (tl_y + tr_y) / 2;
        if (y <= tm_y)
            update_y(x, y, id_x, tl_x, tr_x, 2 * id_y, tl_y, tm_y);
        else
            update_y(x, y, id_x, tl_x, tr_x, 2 * id_y + 1, tm_y + 1, tr_y);
      
        T[id_x][id_y] = T[id_x][2 * id_y] + T[id_x][2 * id_y + 1];
    }
}

void update_x(int x, int y, int id_x = 1, int tl_x = 1, int tr_x = n) {
    if (tl_x != tr_x) {
        int tm_x = (tl_x + tr_x) / 2;
        if (x <= tm_x) 
            update_x(x, y, 2 * id_x, tl_x, tm_x);
        else 
            update_x(x, y, 2 * id_x + 1, tm_x + 1, tr_x);
    }
    update_y(x, y, id_x, tl_x, tr_x);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        s = " " + s;
        for (int j = 1; j <= n; j++) {
            a[i][j] = (s[j] == '*');
        }
    }

    build_x();
    
    while(q--) {
        int op; cin >> op;
        if (op == 1) {
            int i,j;
            cin >> i >> j;
            update_x(i, j);
        } else {
            int i1,j1,i2,j2;
            cin >> i1 >> j1 >> i2 >> j2;
            cout << query_x(i1, i2, j1, j2) << '\n';
        }
    }

    return 0;
}
