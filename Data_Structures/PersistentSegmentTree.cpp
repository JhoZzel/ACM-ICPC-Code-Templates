// Persistent Segment Tree
//

const int N = 1e5 + 5;
const int LOG = 17;
const int NODES = (4 + LOG) * N;

int n,m,q;
int nodes;
int a[N];
int root[N];
int L[NODES];
int R[NODES];
int T[NODES];

int new_leaf(int x) {
    int id = ++nodes;
    L[id] = R[id] = -1;
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

int build(int tl = 0, int tr = m - 1) { 
    if (tl == tr) return new_leaf(0);
    int tm = (tl + tr) / 2; 
    return new_par(build(tl, tm), build(tm + 1, tr));
}

int update(int id, int pos, int x, int tl = 0, int tr = m - 1) { // root id (version)
    if (tl == tr) return new_leaf(T[id] + x);
    int tm = (tl + tr) / 2;
    if (pos <= tm) return new_par(update(L[id], pos, x, tl, tm), R[id]);
    return new_par(L[id], update(R[id], pos, x, tm + 1, tr));
}

int query(int l_id, int r_id, int k, int tl = 0, int tr = m - 1) { // kth smallest 1-indexed
    if (tl == tr) return tl; // k >= 1
    int tm = (tl + tr) / 2;
    int freq = T[L[r_id]] - T[L[l_id]];
    if (k <= freq) return query(L[l_id], L[r_id], k, tl, tm);
    return query(R[l_id], R[r_id], k - freq, tm + 1, tr);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    // compress
    vector<int> t(a + 1, a + n + 1);
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    m = t.size(); // number of different elements

    // building versions of ST
    root[0] = build();
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(t.begin(), t.end(), a[i]) - t.begin();
        root[i] = update(root[i - 1], pos, 1);
    }
    
    while(q--) {
        int l,r,k;
        cin >> l >> r >> k;
        int j = query(root[l - 1], root[r], k);
        cout << t[j] << '\n';
    }

    return 0;
}
