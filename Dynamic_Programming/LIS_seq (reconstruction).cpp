#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
#define all(x) x.begin(), x.end()
#define sz(x) ((int) x.size())
#define F first
#define S second
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

const int INF = 1e9 + 5;

vector<int> LIS_seq(vector<int> &v) { 
    const int n = v.size();
    vector<ii> a;
    for (int i = 0; i < n; i++) {
        a.emplace_back(v[i], i);
    }
    
    vector<ii> d(n + 1, {INF,-1});
    vector<int> par(n, -1);
    d[0] = {-INF,-1};
    for (int i = 0; i < n; i++) {
        int l = 0, h = n;
        while(l < h) {
            int m = (l + h) / 2;
            if (d[m].F <= a[i].F) l = m + 1;
            else h = m;
        }
        if (d[l - 1].F < a[i].F and a[i].F < d[l].F) {
            d[l] = a[i];
            par[a[i].S] = d[l - 1].S;
        }
    }
    
    int LIS = n;
    while(d[LIS].F == INF) LIS--;
    int root = d[LIS].S;

    vector<int> LIS_seq;
    while (root != -1) {
        LIS_seq.push_back(root);
        root = par[root];
    }
    reverse(all(LIS_seq));
    
    return LIS_seq;
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    vector<int> LS = LIS_seq(a);
    for (int i: LS) cout << a[i] << " ";
}

