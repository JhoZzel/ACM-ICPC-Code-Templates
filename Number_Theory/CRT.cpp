#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
using namespace std;
typedef long long ll;

ll exGCD(ll a, ll b, ll &x_0, ll &y_0) {
    if (b == 0) { 
        x_0 = 1;
        y_0 = 0;
        return a;
    }  
    ll x_1, y_1;
    ll g = exGCD(b, a % b, x_1, y_1);
    x_0 = y_1;
    y_0 = x_1 - (a / b) * y_1;
    return g;
}

ll crt(ll a1, ll m1, ll a2, ll m2) {
    if (m1 > m2) swap(a1,a2), swap(m1,m2);
    ll x, y, g = exGCD(m1, m2, x, y);
    if ((a1 - a2) % g != 0) return -1; // doesn't exist
    //assert((a1 - a2) % g == 0);
    x = a1 + (a2 - a1) % m2 * x % m2 / g * m1;
    return x < 0 ? x + m1 * m2 / g : x;
}

ll lcm(ll n1, ll n2) {
    return n1 / __gcd(n1,n2) * n2;
}

int main() {
	ll a1 = 4, m1 = 12, a2 = 3, m2 = 7;
    ll x = crt(a1,m1,a2,m2);
    cout << x << " " << lcm(m1,m2) << "\n";
    return 0;
}
