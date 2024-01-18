#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define sz(x) ((int) x.size())
using namespace std;
typedef long long ll;

const int N = 3e3 + 5;

string a,b;
int dp[N][N];
bool vis[N][N];

int DP(int i, int j) {
    if (i == sz(a) or j == sz(b)) return 0;
    if (vis[i][j]) return dp[i][j];
    vis[i][j] = true;
    if (a[i] == b[j]) return dp[i][j] = 1 + DP(i + 1, j + 1);
    return dp[i][j] = max(DP(i + 1, j), DP(i, j + 1));
}

string rec(int i, int j) {
    if (i == sz(a) or j == sz(b)) return "";
    if (DP(i,j) == 1 + DP(i + 1, j + 1) and a[i] == b[j]) return a[i] + rec(i + 1, j + 1);
    if (DP(i,j) == DP(i + 1, j)) return rec(i + 1, j);
    if (DP(i,j) == DP(i, j + 1)) return rec(i, j + 1);
}

int main() {
    cin >> a >> b;
    cout << rec(0,0) << endl;
    return 0;
}

