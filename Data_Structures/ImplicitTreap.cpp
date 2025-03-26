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

const int N = 1e5 + 5;

int n,q;
int a[N]; 
vector<int> sol;

// Treap

int sz(node *t) {
    return (t ? t->cnt : 0);
}

void update(node *&t) {
    if (t) t->cnt = sz(t->left) + 1 + sz(t->right);
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

node* build(int l = 0, int r = n - 1) { 
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    node *t = new node(a[mid]);
    t->left = build(l, mid - 1);
    t->right = build(mid + 1, r);
    heapify(t);
    update(t);
    return t;
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

void dfs(node *t) {
    if (!t) return;
    dfs(t->left);
    sol.push_back(t->key);
    dfs(t->right);
}

// Fenwick Tree

int FT[N];
void update_FT(int i, int x) {
    for (++i; i < N; i += i & -i) FT[i] = max(FT[i], x);
}
int query_FT(int i) {
    int mx = 0;
    for (++i; i > 0; i -= i & -i) mx = max(mx, FT[i]);
    return mx;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> q; 
    for (int i = 0; i < n; i++) a[i] = i;

    node *t = build();
    while(q--) {
        int i,j;
        cin >> i >> j;
        auto [L, mid] = split(t, i - 1);
        auto [s, R] = split(mid, 1);
        t = merge(L, R);
        auto [l, r] = split(t, j - 1);
        t = merge(l, s);
        t = merge(t, r);
    }
    dfs(t);

    int lis = 1;
    for (int i = 0; i < n; i++) {
        int dp = query_FT(sol[i] - 1) + 1;
        update_FT(sol[i], dp);
        lis = max(lis, dp);
    }
    cout << n - lis << '\n';

    return 0;
}
