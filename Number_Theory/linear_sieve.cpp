#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << " = " << x << endl
#define pv(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define raya cerr << string(20, '=') << endl

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define eb emplace_back
#define ff first
#define ss second

typedef long long ll;

const int MAX = 1e7 + 5;

int spf[MAX];
vector<int> primes;

void sieve() {
    for (int i = 2; i < MAX; i++) {
        if (spf[i] == 0) spf[i] = i, primes.push_back(i);
        for (int j = 0; i * primes[j] < MAX; j++) {
            spf[i * primes[j]] = primes[j];
            if (primes[j] == spf[i]) break;
        }
    }
}

vector<int> get_fact(int x) {
    vector<int> f;
    while(x != 1) {
        f.push_back(spf[x]);
        x /= spf[x];
    }       
    return f;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    sieve();
    int q; cin >> q;
    while(q--) {
        int n; cin >> n;
        vector<int> f = get_fact(n);
        for (int e : f) cout << e << " ";
        cout << '\n';
    }
    return 0;
}
