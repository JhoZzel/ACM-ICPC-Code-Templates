// Preffix Sum 2D
//

using ll = long long;

const int N = 1000 + 5;

int n,m,q;
int a[N][N];
ll pre[N][N];

ll sum(int x1, int y1, int x2, int y2) {
    return pre[x2][y2] - pre[x2][y1 - 1] - pre[x1 - 1][y2] + pre[x1 - 1][y1 - 1];
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> m; 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            pre[i][j] = a[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
    }
    
    cin >> q;
    while (q--) {
        int x1,x2,y1,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << sum(x1, y1, x2, y2) << '\n';
    }

    return 0;
}
