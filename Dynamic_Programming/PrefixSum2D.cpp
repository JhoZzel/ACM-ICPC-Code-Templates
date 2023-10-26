#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
    int n; cin >> n;
    vvi a(n + 1, vi(n + 1));
    vvi pre(n + 1 ,vi(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            pre[i][j] = a[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
    }
    
    int x1 = 4, y1 = 8;
    int x2 = 6, y2 = 8;
    
    int val = pre[x2][y2] - pre[x2][y1 - 1] - pre[x1 - 1][y2] + pre[x1 - 1][y1 - 1];
    cout << val << endl;
    return 0;
}


