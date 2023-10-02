#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

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

ll lcm(ll a, ll b) {
    return a / __gcd(a,b) * b;
}

int main() {
	int n; cin >> n;
    vii s;
    for (int i = 0; i < n; i++) {
        int a,m;
        cin >> a >> m;
        s.emplace_back(a,m);
    }
    
    ll a_now = crt(s[0].F, s[0].S, s[1].F, s[1].S);
    ll m_now = lcm(s[0].S, s[1].S); 

    for (int i = 2; i < n; i++) {
        int a = s[i].F;
        int m = s[i].S;
        a_now = crt(a_now, m_now, a, m);
        m_now = lcm(m_now, m);
    }
    cout << a_now << " " << m_now << "\n";
    
    return 0;
}
