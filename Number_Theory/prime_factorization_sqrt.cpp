#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<int,int> get_fact(ll n) {
    map<int,int> mp;
    for (int i = 2; 1ll * i * i <= n; i++) {
        int e = 0;
        while(n % i == 0) {
            n /= i;
            e++;
        }
        if (e == 0) continue;
        mp[i] = e;
    }
    if (n > 1) mp[n]++;
    return mp;
}

int main() {
    ll n = 1402979760;
    map<int,int> fact = get_fact(n);
    for (auto [x, e] : fact) {
        cout << x << " ^ " << e << "\n";
    }
    return 0;
}
