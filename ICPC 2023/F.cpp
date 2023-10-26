#include<bits/stdc++.h>
#define pr_v(x) for (auto e : x) cout << e << " "; cout << "\n"
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) ((int) x.size())
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

vi get_base(ll n, int b) {
    vi cif;
    while(n) {
	int r = n % b;
	cif.push_back(r);
	n = (n - r) / b;
    }
    return cif;
}

bool is_pal(vi cif) {
    const int m = sz(cif);
    for (int i = 0; i < m / 2; i++) {
        if (cif[i] != cif[m - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int sqrt_l(ll N) { // b ^ 2 + 1 <= N (max b)
    int lo = 0, hi = 1e9 + 5;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (1ll * mid * mid + 1 <= N) lo = mid; 
        else hi = mid - 1;
    }
    return lo;
}

set<ll> get_div(ll N) {
    set<ll> div;
    for (int i = 1; 1ll * i * i <= N; i++) {
        if (N % i == 0) {
            div.insert(i);
            div.insert(N / i);
        }
    }
    return div;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    set<ll> bases;
    int b = sqrt_l(N);
    for (int i = 2; i <= b; i++) {
        if (is_pal(get_base(N,i))) {
            bases.insert(i);
        }
    }
    
    set<ll> div = get_div(N);
    for (ll d : div) {
        if (d - 1 > b and N / d < d - 1) {
            bases.insert(d - 1);
        }
    }
    if (sz(bases) == 0) cout << "*";
    else {
        for (ll k : bases) {
            cout << k << " ";
        }
    }
    return 0;
}


