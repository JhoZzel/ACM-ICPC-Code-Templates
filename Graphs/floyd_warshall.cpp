#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
using namespace std;

const int INF = 2e9 + 5;
const int N = 100 + 5;

int n;
int m;
int dis[N][N];

int main() {
    fast_io;
    cin >> n >> m;
    
    // Initialize dis matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dis[i][j] = 0;
            else dis[i][j] = INF;
        }
    }

    // Input
    for (int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        dis[u][v] = min(dis[u][v], w);
    }

    // Floyd Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++){
                int d = dis[i][k] + dis[k][j];
                if (dis[i][k] == INF or dis[k][j] == INF) continue;
                if (d < dis[i][j]) {
                    dis[i][j] = d;
                }
            }
        }
    }
 
    for (int i = 0; i < n; i++) {
        if (dis[i][i] < 0) {
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dis[i][j] < INF) cout << dis[i][j] << " ";
            else cout << "INF ";
        }
        cout << "\n";
    }

    return 0;
}
