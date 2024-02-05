#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
int level[N];
vector<int> G[N];

pair<int,int> get_furthest(int s0) {
    queue<int> Q;
    Q.push(s0);
    fill(level, level + n, -1);
    level[s0] = 0;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int w : G[u]) {
            if (level[w] != -1) continue;
            level[w] = level[u] + 1;
            Q.push(w);
        }
    }
    
    int far_node = 0;
    for (int i = 0; i < n; i++) {
        if (level[i] > level[far_node]) {
            far_node = i;
        }
    }
    return make_pair(far_node, level[far_node]);
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

