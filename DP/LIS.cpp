// LIS
//

#define all(x) x.begin(), x.end()

const int INF = 1e9 + 5;

int LIS(vector<int> &a) { 
    const int n = a.size();
    vector<int> d(n + 1, INF);
    d[0] = -INF;
   
    for (int i = 0; i < n; i++) {
        int j = lower_bound(all(d), a[i]) - d.begin();
        if (a[i] < d[j] and d[j - 1] < a[i]) {
            d[j] = a[i];
        }
    }

    int len = n;
    while(d[len] == INF) len--;
    return len;
}
