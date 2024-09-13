#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
int dis[N];
vector<int> G[N];

pair<int,int> get_furthest(int s0) {
    queue<int> Q({s0});
    fill(dis, dis + n, -1);
    dis[s0] = 0;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int w : G[u]) {
            if (dis[w] != -1) continue;
            dis[w] = dis[u] + 1;
            Q.push(w);
        }
    }
    int far = 0;
    for (int i = 0; i < n; i++) if (dis[i] > dis[far]) far = i;
    return {far, dis[far]};
}

int get_diameter() {
    return get_furthest(get_furthest(0).first).second;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    cout << get_diameter() << "\n";
    return 0;
}
