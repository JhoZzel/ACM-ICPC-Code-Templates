#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int n,m;
vvi ady;
vector<int> in;

vector<int> top_order() {
    vector<int> order;
    queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (in[i]) continue;
        Q.push(i);
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int w : ady[u]) {
            if (--in[w] == 0) Q.push(w);
        }
        order.push_back(u);
    }
    return (order.size() < n) ? vector<int>() : order;
}

int main() {
    cin >> n >> m;
    ady.resize(n);
    in.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ady[u].push_back(v);
        in[v]++;
    }
    vector<int> order = top_order();
    for (int e : order) cout << e << " ";
    return 0;
}
