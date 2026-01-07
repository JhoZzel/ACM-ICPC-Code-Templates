// Block Treap
//

using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

int len_mx;

struct node {
    int val; // valor actual
    int len; // tamano del bloque
    int cnt; // tamano del arbol
    int pr;
    node *left, *right;
    node() {}
    node(int x, int y) : val(x), len(y) {
        cnt = len;
        pr = random(0, 1e9);
        left = right = nullptr;
    }
    void dbg() {
        cerr << this << endl;
        cerr << "val: " << val << endl;
        cerr << "len: " << len << endl;
        cerr << "cnt: " << cnt << endl;
        cerr << "pr: " << pr << endl;
        cerr << "l: " << left << "  r: " << right << endl;
        cerr << "===============\n";
    }
};

int sz(node *t) {
    return t ? t->cnt : 0;
}

void update(node *t) {
    if (!t) return;
    t->cnt = sz(t->left) + t->len + sz(t->right);
}

void heapify(node *t) { 
    if (!t) return;
    node *mx = t;
    if (t->left and t->left->pr > mx->pr) 
        mx = t->left;
    if (t->right and t->right->pr > mx->pr) 
        mx = t->right;
    if (mx != t) {
        swap(t->pr, mx->pr);
        heapify(mx);
    }
}

node* build(vector<pair<int,int>> &b, int l, int r) { 
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    auto [x, y] = b[mid];
    node *t = new node(x, y);
    t->left = build(b, l, mid - 1);
    t->right = build(b, mid + 1, r);
    heapify(t);
    update(t);
    return t;
}

node* merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    node* t;
    if (l->pr > r->pr) {
        t = l;
        t->right = merge(l->right, r);
    } else {
        t = r;
        t->left = merge(l, r->left);
    }
    update(t);
    return t;
}

pair<node*, node*> split(node *t, int k) { 
    if (!t) return {nullptr, nullptr};
    
    if (k > sz(t->left) and k < sz(t->left) + t->len) { // divide el bloque
        int x1 = k - sz(t->left);
        int x2 = t->len - x1;
        int v = t->val;
        node *s1 = new node(v, x1);
        node *s2 = new node(v, x2);
        node *l = merge(t->left, s1);
        node *r = merge(s2, t->right);
        update(l); update(r);
        return {l, r};
    }

    node *l,*r;
    if (k < sz(t->left) + t->len) {
        r = t;
        auto [L, R] = split(t->left, k); 
        r->left = R;
        l = L;
    } else {
        l = t;
        auto [L, R] = split(t->right, k - sz(t->left) - t->len);
        l->right = L;
        r = R;
    }
    update(l); update(r);
    return {l, r};
}

node* query_left(node *t) {
    if (!t) return nullptr;
    if (!t->left) return t;
    return query_left(t->left);
}

node* query_right(node *t) {
    if (!t) return nullptr;
    if (!t->right) return t;
    return query_right(t->right);
}

node* good_merge(node *l, node *r) {
    node *s1,*s2;
    while(l and r) {
        s1 = query_right(l);
        s2 = query_left(r);
        if (s1->val != s2->val) break;
        if (s1->len + s2->len >= len_mx) {
            int len1 = sz(l) - s1->len;
            int len2 = s2->len;
            tie(l, s1) = split(l, len1);
            tie(s2, r) = split(r, len2);
        } else {
            int len1 = sz(l) - s1->len;
            int len2 = s2->len;
            tie(l, s1) = split(l, len1);
            tie(s2, r) = split(r, len2);
            node *s = new node(s1->val, s1->len + s2->len);
            l = merge(l, s);
        }
    }
    return merge(l, r);
}


void pv(node *t) {
    if (!t) return;
    pv(t->left);
    cerr << t->val << "/" << t->len << " ";
    pv(t->right);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n,q;
    cin >> n >> len_mx >> q;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    vector<pair<int,int>> b; 
    int cnt = 1, key = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] == key) cnt++;
        else {
            b.emplace_back(key, cnt);
            cnt = 1;
            key = a[i];
        }
   }
    b.emplace_back(key, cnt);

    node *t = build(b, 0, (int)b.size() - 1);
    while(q--) {
        int p,x;
        cin >> p >> x;
        auto [l, r] = split(t, p);
        node *s = new node(x, 1);
        t = good_merge(l, s);
        t = good_merge(t, r);
        cout << sz(t) << "\n";
    }

    return 0;
}
