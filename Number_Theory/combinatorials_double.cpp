#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll C(int n, int k) {
    long double res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return (ll) (res + 0.01);
}


int main() {
    int n,k;
    cin >> n >> k;
    cout << C(n,k) << "\n";
    return 0;
}
