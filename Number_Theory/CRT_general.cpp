#include <bits/stdc++.h>
using namespace std;

#define ff first
#define ss second

using ll = long long;

ll exGCD(ll a, ll b, ll &x0, ll &y0) {
    if (b == 0) { 
        x0 = 1;
        y0 = 0;
        return a;
    }  
    ll x1, y1, g = exGCD(b, a % b, x1, y1);
    x0 = y1; y0 = x1 - (a / b) * y1;
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

ll lcm(ll a, ll b) {
    return a / gcd(a,b) * b;
}

int main() {
    int n; cin >> n;
    vector<pair<int,int>> s; // [a, mod]
    for (int i = 0; i < n; i++) cin >> s[i].ff >> s[i].ss;
    
    ll a_now = crt(s[0].ff, s[0].ss, s[1].ff, s[1].ss);
    ll m_now = lcm(s[0].ss, s[1].ss); 

    for (int i = 2; i < n; i++) {
        int a = s[i].ff;
        int m = s[i].ss;
        a_now = crt(a_now, m_now, a, m);
        m_now = lcm(m_now, m);
    }
    cout << a_now << " " << m_now << "\n";
    
    return 0;
}
