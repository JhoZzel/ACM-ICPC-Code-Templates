#include <bits/stdc++.h>
using namespace std;

int solve(vector<pair<int,int>> a, int W) {
    vector<int> last(W + 1, 0);
    for (auto [v, w] : a) {
        vector<int> cur(last);
        for (int cap = 0; cap <= W; cap++) {
            if (cap - w >= 0)
                cur[cap] = max(cur[cap], last[cap - w] + v);
        }
        swap(cur, last);
    }
    return last[W];
}

int main() {
    int n,C; 
    cin >> n >> C;
    vector<pair<int,int>> a;
    for (int i = 0; i < n; i++) {
        int v,w;
        cin >> v >> w;
        a.emplace_back(v, w);
    }
    cout << solve(a, C) << '\n';
}
