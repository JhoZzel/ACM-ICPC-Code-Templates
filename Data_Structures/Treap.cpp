#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
int random(int l, int r) { 
    return uniform_int_distribution<int>(l, r)(rng); 
}

struct node {
    int val, pr;
    node *left;
    node *right;
    node (int x) : val(x) {
        pr = random(0, 1e9);
        left = right = nullptr;
    }
};  

pair<node*, node*> split(int x, node *t) {
    if (t == nullptr) return {nullptr, nullptr};
    if (x >= t->val) {
        auto p = split(x, t->right);
        t->right = p.ff;
        return  {t, p.ss};
    } 
    else {
        auto p = split(x, t->left);
        t->left = p.ss;
        return {p.ff, t};
    }
}

node* merge(node *l, node *r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    if (l->pr > r->pr) {
        l->right = merge(l->right, r);
        return l;
    } 
    else {
        r->left = merge(l, r->left);
        return r;
    }
}


node* add(int x, node *t) {
    auto [L, R] = split(x, t);
    node *new_node = new node(x);
    return t = merge(merge(L, new_node), R);
}

int main() {
    node x(12);
    cout << x.val << " " << x.pr << endl;
    return 0;
}
