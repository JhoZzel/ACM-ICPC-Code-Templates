mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node {
    int key,pr,cnt;
    node *left, *right;
    node(int x) {
        key = x;
        cnt = 1;
        pr = random(0, 1e9);
        left = right = nullptr;
    }
};

int sz(node *t) {
    return (t ? t->cnt : 0);
}

void update(node *t) {
    if (!t) return;
    t->cnt = sz(t->left) + 1 + sz(t->right);
}

pair<node*, node*> split(node *t, int x) {
    if (!t) return {nullptr, nullptr};
    node *l,*r;
    if (t->key <= x) {
        l = t;
        auto [L, R] = split(t->right, x);
        l->right = L;
        r = R;
    } else {
        r = t;
        auto [L, R] = split(t->left, x);
        r->left = R;
        l = L;
    }
    update(l); update(r);
    return {l, r};
}

pair<node*, node*> split(node *t, int k) { 
    if (k == 0) return {nullptr, t};
    node *l,*r;
    if (k < sz(t->left) + 1) {
        r = t;
        auto [L, R] = split(t->left, k); 
        r->left = R;
        l = L;
    } else {
        l = t;
        auto [L, R] = split(t->right, k - sz(t->left) - 1);
        l->right = L;
        r = R;
    }
    update(l); update(r);
    return {l, r};
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

node* build(vector<int> &a, int l, int r) { 
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    node *t = new node(a[mid]);
    t->left = build(a, l, mid - 1);
    t->right = build(a, mid + 1, r);
    heapify(t);
    update(t);
    return t;
}

node* find(node *t, int x) {
    if (!t) return nullptr;
    if (t->key == x) 
        return t;
    if (t->key < x) 
        return find(t->right, x);
    else 
        return find(t->left, x);
}

node* insert(node *t, node *s) {
    if (!t) return s;
    if (s->pr > t->pr) {
        auto [l, r] = split(t, s->key);
        s->left = l;
        s->right = r;
        t = s;
    } else if (s->key < t->key) {
        t->left = insert(t->left, s);
    } else {
        t->right = insert(t->right, s);
    }
    update(t);
    return t;
}

node* erase(node *t, int x) {
    if (!t) return nullptr;
    if (t->key == x) 
        t = merge(t->left, t->right);
    else if (x < t->key) 
        t->left = erase(t->left, x);
    else 
        t->right = erase(t->right, x);
    update(t);
    return t;
}

int count(node *t, int x) { // #elem <= x
    if (!t) return 0;
    if (t->key <= x) 
        return 1 + sz(t->left) + count(t->right, x);
    else 
        return count(t->left, x);
}

int get_kth(node *t, int k) {
    if (k == sz(t->left) + 1) return t->key;
    int cnt = sz(t->left) + 1;
    if (k > cnt) 
        return get_kth(t->right, k - cnt);
    else
        return get_kth(t->left, k);
}
