#include <bits/stdc++.h>
using namespace std;

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

int get_kth(node *t, int k) {
    if (k == sz(t->left) + 1) return t->key;
    int cnt = sz(t->left) + 1;
    if (k > cnt) 
        return get_kth(t->right, k - cnt);
    else
        return get_kth(t->left, k);
}

int cnt(node *t, int x) {
    if (!t) return 0;
    if (t->key < x) 
        return 1 + sz(t->left) + cnt(t->right, x);
    else
        return cnt(t->left, x);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int q; cin >> q;
    node *t = nullptr;
    while(q--) {
        char op; cin >> op;
        if (op == 'I') {
            int x; cin >> x;
            if (not find(t, x)) {
                t = insert(t, new node(x));
            }
        } else if (op == 'D') {
            int x; cin >> x;
            t = erase(t, x);
        } else if (op == 'K') {
            int k; cin >> k;
            if (k > sz(t)) cout << "invalid\n";
            else cout << get_kth(t, k) << '\n';
        } else {
            int x; cin >> x;
            cout << cnt(t, x) << '\n';
        }
    }
    return 0;
}

// https://www.spoj.com/problems/ORDERSET/
