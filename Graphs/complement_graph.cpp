#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define print_v(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(15, '=') << endl

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define ff first
#define ss second

typedef long long ll;

const int N = 5e5 + 5;

int n;
int m;
set<int> S;
vector<int> G[N];
vector<vector<int>> ans;
vector<int> comp;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }
    for (int i = 0; i < n; i++) S.emplace(i);
    for (int i = 0; i < n; i++) {
        if (!S.count(i)) continue;
        vector<int> comp = {i};
        queue<int> Q;
        Q.push(i);
        S.erase(i);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            set<int> to(S);
            for (int v : G[u]) to.erase(v);
            for (int v : to) {
                Q.push(v);
                comp.eb(v);
                S.erase(v);
            }
        }
        ans.eb(comp);
    }
    cout << sz(ans) << '\n';
    for (auto v : ans) {
        cout << sz(v) << ' ';
        for (int e : v) cout << e << ' ';
        cout << '\n';
    }
    return 0;
}
