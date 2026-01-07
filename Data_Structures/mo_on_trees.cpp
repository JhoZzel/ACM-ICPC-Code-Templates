// Mo on Trees
//

// Values on the vertex 
// Be careful with the size of block 2 * N

#define all(x) x.begin(), x.end()

const int B = 317; 

struct Query {
    int l, r, z, idx;
    bool operator < (const Query other) const {
        int block_a = l / B, block_b = other.l / B;
        if (block_a != block_b) return block_a < block_b;
        return ((block_a & 1) ? (r > other.r) : (r < other.r)); 
    }
};

const int N = B * B; 
const int LOG = 20; 

// Building lca - binary lifting ...

void update(int x, int del) {
    
}

vector<int> mo_algorithm(vector<Query> Q) {
    vector<int> ans(Q.size());

    sort(all(Q));

    vector<int> p(n, 0);
    auto move = [&](int idx) {
        int u = euler[idx];
        p[u] ^= 1;
        int add = p[u] ? 1 : -1;
        update(a[u], add);
    };     

    int cur_l = 0, cur_r = -1; // euler
    for (Query q : Q) {
        while (cur_l > q.l) move(--cur_l);
        while (cur_r < q.r) move(++cur_r);
        while (cur_l < q.l) move(cur_l++);
        while (cur_r > q.r) move(cur_r--);
        if (q.z != -1) move(q.z);
        ans[q.idx] = res;
        if (q.z != -1) move(q.z);
    }

    return ans;
}


void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    dfs(0); 

    // Build euler tour
    for (int i = 0; i < n; i++) {
        euler[tin[i]] = euler[tout[i]] = i; 
    }

    cin >> q;
    vector<Query> Q;
    for (int i = 0; i < q; i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        if (tin[u] > tin[v]) swap(u, v);
        int w = lca(u, v);
        if (w == u) {
            Q.push_back({tin[u], tin[v], -1, i});
        } else {
            Q.push_back({tout[u], tin[v], tin[w], i});
        }
    }
    
    vector<int> ans = mo_algorithm(Q);
    for (int e : ans) cout << e << "\n";
}
