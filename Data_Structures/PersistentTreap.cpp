#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node {
    int pr;
    int cnt;
    vector<int> freq;
    int x;
    node *left;
    node *right;
    node() {}
    node(int sym) {
        pr = random(0, 1e9);
        cnt = 1;
        freq = vector<int>(4, 0);
        freq[sym] = 1;
        x = sym;
        left = right = nullptr;
    }
    friend node* copy(node *p) {
        if (!p) return nullptr;
        node *s = new node();
        s->pr = p->pr;
        s->cnt = p->cnt;
        s->freq = p->freq; 
        s->left = p->left;
        s->right = p->right;
        s->x = p->x;
        return s;
    }
};

const int N = 1e4 + 4;

node *root[N];

// Treap

int sz(node *t) {
    return (t ? t->cnt : 0);
}

void update(node *t) {
    if (!t) return;
    t->cnt = sz(t->left) + 1 + sz(t->right);
    t->freq.assign(4, 0);
    for (int i = 0; i < 4; i++) {
        if (t->left) t->freq[i] += t->left->freq[i];
        if (t->right) t->freq[i] += t->right->freq[i];
    }
    t->freq[t->x] += 1;
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

int T(char x) {
    if (x == 'A') return 0;
    if (x == 'G') return 1;
    if (x == 'T') return 2;
    if (x == 'C') return 3;
    return -1;
}

node* build(string &s, int l, int r) { 
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    node *t = new node(T(s[mid]));
    t->left = build(s, l, mid - 1);
    t->right = build(s, mid + 1, r);
    heapify(t);
    update(t);
    return t;
}

pair<node*, node*> split(node *t, int k) {
    if (k == 0) return {nullptr, copy(t)};
    node *l,*r;
    if (k < sz(t->left) + 1) {
        r = copy(t);
        auto [L, R] = split(r->left, k); 
        r->left = R;
        l = L;
    } else {
        l = copy(t);
        auto [L, R] = split(l->right, k - sz(l->left) - 1);
        l->right = L;
        r = R;
    }
    update(l); update(r);
    return {l, r};
}

node* modify(node *t, int k, int nx) {
    node *s = copy(t);
    if (k == sz(s->left) + 1) {
        s->freq[s->x] -= 1;
        s->freq[nx] += 1;
        s->x = nx;
    } else if (k < sz(s->left) + 1) {
        s->left = modify(s->left, k, nx);
    } else {
        s->right = modify(s->right, k - sz(s->left) - 1, nx);
    }
    update(s);
    return s;
}

node* merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    node* t;
    if (l->pr > r->pr) {
        t = copy(l);
        t->right = merge(t->right, r);
    } else {
        t = copy(r);
        t->left = merge(l, t->left);
    }
    update(t);
    return t;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    int free_id = n + 1;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        const int len = s.size();
        root[i] = build(s, 0, len - 1);
    } 
    int q; cin >> q;
    while(q--) {
        string op; cin >> op;
        if (op == "CROSS") {
            int id1,id2,k1,k2;
            cin >> id1 >> id2 >> k1 >> k2;
            auto [l1, r1] = split(root[id1], k1); 
            auto [l2, r2] = split(root[id2], k2); 
            root[free_id++] = merge(l1, r2);
            root[free_id++] = merge(l2, r1);
        } else if (op == "MUTATE") {
            char m;
            int id,k;
            cin >> id >> k >> m;
            root[id] = modify(root[id], k, T(m));
        } else {
            int id,k1,k2;
            cin >> id >> k1 >> k2;
            auto [l, R] = split(root[id], k2);
            auto [L, mid] = split(l, k1 - 1);
            for (int i = 0; i < 4; i++) {
                cout << mid->freq[i] << " \n"[i == 3];
            }
        }
    }
    return 0;
}

// https://vn.spoj.com/problems/GENETICS/
