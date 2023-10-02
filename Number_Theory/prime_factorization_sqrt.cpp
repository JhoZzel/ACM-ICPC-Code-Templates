#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

vii prime_factorization(ll n) {
    vii p;
    for (int i = 2; 1ll * i * i <= n; i++) {
        if (n % i == 0) {
            int e = 0;
            while (n % i == 0) {
                e++;
                n/=i;
            }
            p.emplace_back(i,e);
        }
    }
    if (n > 1) 
        p.emplace_back(n,1);
    return p;
}

int main() {
    ll n = 1402979760;
    vii p = prime_factorization(n);
    for (ii e : p) cout << e.F << " " << e.S << "\n";
    return 0;
}
