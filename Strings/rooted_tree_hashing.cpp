// Rooted Tree Hashing
//

const int N = 1e5 + 5;
const int MOD = 1e9 + 9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int n;
int H[N];
vector<int> G[2][N];

void clean() {
    for (int id = 0; id < 2; id++) 
        fill(G[id], G[id] + n, vector<int>());
}

int dfs(int id, int u, int p = 0, int d = 0) {
    int hs = 1;
    for (int v : G[id][u]) {
        if (v == p) continue;
        hs = 1ll * hs * (H[d] + dfs(id, v, u, d + 1)) % MOD;
    }
    return hs;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    for (int i = 0; i < N; i++) {
        H[i] = uniform_int_distribution(N + 1, MOD - 1)(rng);
    }

    int t; cin >> t;
    while(t--) {
        cin >> n;
        for (int id = 0; id < 2; id++) {
            for (int i = 0; i < n - 1; i++) {
                int u,v;
                cin >> u >> v;
                u--; v--;
                G[id][u].push_back(v);
                G[id][v].push_back(u);
            }
        }
        int r1 = dfs(0, 0);
        int r2 = dfs(1, 0);
        cout << (r1 == r2 ? "YES" : "NO") << '\n';

        clean();
    }

    return 0;
}
