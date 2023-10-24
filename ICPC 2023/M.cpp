#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie (0); cout.tie(0)
#define dbg(x) do {cerr << #x <<" = " << (x) << endl; } while (false)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define sz(x) ((int) x.size())
#define F first
#define S second
using namespace std;
using u128 = __uint128_t;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef priority_queue<ii, vii, greater<ii>> pq_min;

const int INF = 1e9;

int n,m;
vector<vii> ady;

void get_adj_list() {
    ady.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        ady[u].eb(v,w);
        ady[v].eb(u,w);
    }
}

vll dijkstra(int s, int skip) {
    vll d(n + 1, INF); 
    d[s] = 0;
    pq_min q;
    q.push({0,s});
    while(!q.empty()) {
        int v = q.top().S;
        int d_v = q.top().F;
        q.pop();
        if (v == skip) {
            continue;
        }
        if (d_v != d[v]) continue;
        for (auto edge : ady[v]) {
            int to = edge.F;
            int len = edge.S;
            if (to == skip) {
                continue;
            }
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
    return d;
}

int main() {
    fast_io;
    int P,G;
    cin >> n >> m >> P >> G;
    get_adj_list();

    vll dij1 = dijkstra(P,-1);
    vll dij2 = dijkstra(P,G);
    ll dis = dij1[G];
    vi ans;

    for (int i = 1; i <= n; i++) {
        if (i == P) continue;
        if (dij1[i] == 2 * dis and dij2[i] > dij1[i]) {
            ans.pb(i);
        }
    }
    if (sz(ans) == 0) {
        cout << "*";
        return 0;
    }
    sort(all(ans));
    for (int e : ans) cout << e << " ";

    return 0;
}
