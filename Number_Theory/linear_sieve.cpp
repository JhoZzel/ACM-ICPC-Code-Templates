#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX = 1e7 + 5;

int spf[MAX];
vector<int> pr;

void sieve() {
    for (int i = 2; i < MAX; i++) {
        if (!spf[i]) spf[i] = i, pr.push_back(i);
        for (int j = 0; i * pr[j] < MAX; j++) {
            spf[i * pr[j]] = pr[j];
            if (pr[j] == spf[i]) break;
        }
    }
}

vector<pair<int,int>> get_fact(int x) {
    vector<pair<int,int>> f;
    while(x != 1) {
        int p = spf[x];
        int e = 0;
        while(x % p == 0) {
            e++;
            x /= p;
        }
        f.emplace_back(p, e);
    }      
    return f;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    sieve();
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        vector<pair<int,int>> f = get_fact(n);
        for (auto [p, e] : f) {
            cout << p << " ^ " << e << endl;
        }
    }
    return 0;
}
