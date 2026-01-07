// DSU - rollback
//

const int N = 2e5 + 5;

int n,q;
int nComp;
int sz[N];
int par[N];

stack<int> checkpoints;
stack<vector<pair<int&, int>>> history;

void init() {
    for (int i = 0; i < n; i++) {
        sz[i] = 1;
        par[i] = i;
    }
    nComp = n;
}

int get(int a) {
    return (a == par[a]) ? a : get(par[a]);
}

void merge(int a, int b) {
    a = get(a); b = get(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);

    vector<pair<int&, int>> changes;
    changes.emplace_back(par[b], par[b]);
    changes.emplace_back(sz[a], sz[a]);
    changes.emplace_back(nComp, nComp);
    history.emplace(changes);

    par[b] = a;
    sz[a] += sz[b];
    nComp -= 1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> q;

    init();
    
    while(q--) {
        string op; cin >> op;
        if (op == "union") {
            int u,v;
            cin >> u >> v;
            u--; v--;
            merge(u, v);
            cout << nComp << "\n";
        } else if (op == "persist") {
            checkpoints.emplace(history.size());
        } else {
            assert(!checkpoints.empty());
            while((int)history.size() > checkpoints.top()) {
                for (auto [x, y] : history.top()) {
                    x = y;
                }
                history.pop();
            }
            checkpoints.pop();
            cout << nComp << "\n";
        }
    }
    
    return 0;
}
