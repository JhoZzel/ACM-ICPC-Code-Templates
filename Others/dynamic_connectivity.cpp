#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

const int N = 3 * 2e5 + 10;

struct Rectangle {
    int l,r,h;
    Rectangle() {}
    Rectangle (int l, int r, int h) : l(l), r(r), h(h) {}
};


int q,m;
int idx[N];
char op[N];
int in[N];
int out[N];
vector<int> t; 
vector<pair<int,int>> queries;
vector<Rectangle> rectangles;

const int NODES = 200 * N;

int nodes;
int T[NODES];
int L[NODES];
int R[NODES];
int lazy[NODES];

int clone(int id) {
    int new_id = ++nodes;
    L[new_id] = L[id];
    R[new_id] = R[id];
    T[new_id] = T[id];
    lazy[new_id] = lazy[id];
    return new_id;
}

int push(int old, int tl, int tr) {
    if (!lazy[old]) return old; 
    int cur = clone(old);

    T[cur] = max(T[cur], lazy[cur]);
    
    if (tl != tr) {
        L[cur] = clone(L[cur]);
        R[cur] = clone(R[cur]);
        lazy[L[cur]] = max(lazy[L[cur]], lazy[cur]);
        lazy[R[cur]] = max(lazy[R[cur]], lazy[cur]);
    }
    
    lazy[cur] = 0;
    return cur;
}

int update(int old, int l, int r, int x, int tl = 0, int tr = m - 1) { 
    int cur = clone(old);
    cur = push(cur, tl, tr);
    if (l > r) return cur;
    if (tl == l and tr == r) {
        lazy[cur] = max(lazy[cur], x);
        cur = push(cur, tl, tr);
    } else {
        int tm = (tl + tr) / 2;
        L[cur] = update(L[cur], l, min(tm, r), x, tl, tm);
        R[cur] = update(R[cur], max(tm + 1, l), r, x, tm + 1, tr);
        T[cur] = min(T[L[cur]], T[R[cur]]);
    }   
    return cur;
}

int query(int cur, int l, int r, int tl = 0, int tr = m - 1) { 
    cur = push(cur, tl, tr);
    if (l > r) return INT_MAX;
    if (tl == l and tr == r) return T[cur];
    int tm = (tl + tr) / 2;
    int valL = query(L[cur], l, min(r, tm), tl, tm);
    int valR = query(R[cur], max(tm + 1, l), r, tm + 1, tr);
    return min(valL, valR);
}


int get_pos(int x) {
    return lower_bound(all(t), x) - t.begin();
} 

vector<int> T_DC[4 * N]; // [l, r, h]

void update_DC(int l, int r, int j, int id = 1, int tl = 0, int tr = q - 1) {
    if (l > r) return;
    if (tl == l and tr == r) {
        T_DC[id].emplace_back(j);
    } else {
        int tm = (tl + tr) / 2;
        update_DC(l, min(r, tm), j, 2 * id, tl, tm);
        update_DC(max(tm + 1, l), r, j, 2 * id + 1, tm + 1, tr);
    }
}

void pv(int cur, int tl = 0, int tr = m - 1) {
    push(cur, tl, tr);
    if (tl == tr) cout << T[cur] << " ";
    else {
        int tm = (tl + tr) / 2;
        pv(L[cur], tl, tm);
        pv(R[cur], tm + 1, tr);
    }
}

void dfs_solve(int root, int id = 1, int tl = 0, int tr = q - 1) {
    int old_nodes = nodes;
    for (int j : T_DC[id]) {
        auto [l, r, h] = rectangles[j];
        root = update(root, l, r, h);
    }

    if (tl == tr) { // is a leaf
        if (op[tl] == '?') {
            auto [l, r] = queries[idx[tl]];
            cout << query(root, l, r) << '\n';
        }
    } else {
        int tm = (tl + tr) / 2;
        dfs_solve(root, 2 * id, tl, tm);
        dfs_solve(root, 2 * id + 1, tm + 1, tr);
    }

    nodes = old_nodes;
}   

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> op[i];
        if (op[i] == '+') {
            int l,r,h;
            cin >> l >> r >> h;
            idx[i] = rectangles.size();
            rectangles.emplace_back(l, r, h);
            in[idx[i]] = i;
            out[idx[i]] = q - 1;
            t.push_back(l);
            t.push_back(r);
            t.push_back(r - 1);
        } else if (op[i] == '-') {
            int j; cin >> j;
            j--;
            idx[i] = j; 
            out[idx[i]] = i;
        } else {
            int l,r;
            cin >> l >> r;
            idx[i] = queries.size();
            queries.emplace_back(l, r);
            t.push_back(l);
            t.push_back(r);
            t.push_back(r - 1);
        }
   }

    sort(all(t));
    t.erase(unique(all(t)), t.end());
    m = t.size();

    for (auto &[l, r, h] : rectangles) {
        l = get_pos(l);
        r = get_pos(r - 1);
    }
    for (auto &[l, r] : queries) {
        l = get_pos(l);
        r = get_pos(r - 1);
    }

    for (int i = 0; i < sz(rectangles); i++) {
        update_DC(in[i], out[i], i);
    }

    dfs_solve(0);

    return 0;
}
