// Lazy Persistent Segment Tree
//

const int N = 1e5 + 6;
const int NODES = 300 * N;

int n,q;
int nodes;
int a[N];
int root[N];
int L[NODES];
int R[NODES];
ll T[NODES];
ll lazy[NODES];

int new_leaf(ll x) {
    int id = ++nodes;
    L[id] = R[id] = 0;
    T[id] = x;
    return id;
}

int new_par(int l_id, int r_id) { 
    int id = ++nodes;
    L[id] = l_id; 
    R[id] = r_id;
    T[id] = T[L[id]] + T[R[id]];
    return id;
}

int copy(int id) {
    int new_id = ++nodes;
    L[new_id] = L[id];
    R[new_id] = R[id];
    T[new_id] = T[id];
    lazy[new_id] = lazy[id];
    return new_id;
}

int build(int tl = 1, int tr = n) { 
    if (tl == tr) return new_leaf(a[tl]);
    int tm = (tl + tr) / 2; 
    return new_par(build(tl, tm), build(tm + 1, tr));
}

int push(int old, int tl, int tr, int x = 0) {
    int cur = copy(old);
    lazy[cur] += x;
    
    if (!lazy[cur]) return cur;

    int len = tr - tl + 1;
    T[cur] += lazy[cur] * len;
    
    if (tl != tr) {
        L[cur] = copy(L[old]);
        R[cur] = copy(R[old]);
        lazy[L[cur]] += lazy[cur];
        lazy[R[cur]] += lazy[cur];
    }
    
    lazy[cur] = 0;
    
    return cur;
}

int update(int old, int l, int r, int x, int tl = 1, int tr = n) { 
    int cur = push(old, tl, tr);
    if (l > r) return cur;
    if (tl == l and tr == r) return push(cur, tl, tr, x);
    int tm = (tl + tr) / 2;
    L[cur] = update(L[cur], l, min(tm, r), x, tl, tm);
    R[cur] = update(R[cur], max(tm + 1, l), r, x, tm + 1, tr);
    T[cur] = T[L[cur]] + T[R[cur]];
    return cur;
}

ll query(int cur, int l, int r, int tl = 1, int tr = n) { 
    cur = push(cur, tl, tr);
    if (l > r) return 0ll;
    if (tl == l and tr == r) return T[cur];
    int tm = (tl + tr) / 2;
    ll valL = query(L[cur], l, min(r, tm), tl, tm);
    ll valR = query(R[cur], max(tm + 1, l), r, tm + 1, tr);
    return valL + valR;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int cur_t = 0;
    root[0] = build();
    while(q--) {
        char op; cin >> op;
        if (op == 'C') {
            int l,r,d;
            cin >> l >> r >> d;
            root[cur_t + 1] =  update(root[cur_t], l, r, d);      
            cur_t++;
        } 
        else if (op == 'Q') {
            int l,r;
            cin >> l >> r;
            cout << query(root[cur_t], l, r) << '\n';
        } 
        else if (op == 'H') {
            int l,r,t;
            cin >> l >> r >> t;
            cout << query(root[t], l, r) << '\n';
        }  
        else {
            int t; cin >> t;
            cur_t = t;
        }
    }

    return 0;
}
