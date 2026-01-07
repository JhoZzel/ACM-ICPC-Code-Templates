// Floyd Warshall
//

using ll = long long;

const int N = 500 + 5;
const ll INF = 1e18 + 5;

int n,m;
ll dis[N][N];

void update(int u, int v, int w) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll d = dis[i][u] + w + dis[v][j];
            if (d < dis[i][j]) {
                dis[i][j] = d; 
            }
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            dis[i][j] = (i == j) ? 0 : INF;


    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        u--; v--;
        ll d = min<ll>(dis[u][v], w);
        dis[u][v] = dis[v][u] = d;
    }

    // Floyd Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++){
                ll d = dis[i][k] + dis[k][j];
                if (d < dis[i][j]) {
                    dis[i][j] = d;
                }
            }
        }
    }
    
    int q; cin >> q;
    while(q--) {
        int u,v,w;
        cin >> u >> v >> w;
        u--; v--;
        update(u, v, w);
        update(v, u, w);
    }

    return 0;
}
