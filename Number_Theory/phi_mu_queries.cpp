#include <bits/stdc++.h>
using namespace std;

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

void get_phi_mu(int n, int &phi, int &mu) {
    while (n != 1) {
        int p = spf[n];
        phi -= phi / p;
        int e = 0;
        while(n % p == 0) {
            n /= p;
            e++;
        }
        mu = (e > 1) ? 0 : -mu;
    }
}

void solve() {
    int n; 
    cin >> n;
    int phi = n, mu = 1;
    get_phi_mu(n, phi, mu);
    cout << phi << " " << mu << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    sieve();
    int q; cin >> q;
    while(q--) {
        solve();
    }
	return 0;
}
