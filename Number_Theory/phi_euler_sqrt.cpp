#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Time complexity: O(sqrt(n))

ll phi_euler(ll n) {
    ll phi = n;
    for (int i = 2; 1ll * i * i <= n; i++) {
        if (n % i != 0) continue;
        while(n % i == 0) n /= i;
        phi -= phi/i;
    }
    if (n > 1) phi -= phi/n;
    return phi;
}

int main() {
    ll n = 5040;
    cout << phi_euler(n) << endl;
    return 0;
}
