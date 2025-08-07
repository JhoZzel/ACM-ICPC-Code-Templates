using ll = long long;
using pll = pair<ll,ll>;

ll exGCD(ll a, ll b, ll &x0, ll &y0) {
    if (b == 0) { 
        x0 = 1;
        y0 = 0;
        return a;
    }  
    ll x1, y1, g = exGCD(b, a % b, x1, y1);
    x0 = y1; 
    y0 = x1 - (a / b) * y1;
    return g;
}

pll crt(pll A, pll B) {
    auto [a1, m1] = A;
    auto [a2, m2] = B;
    if (m1 == -1 or m2 == -1) return {0, -1};
    if (m1 > m2) swap(a1, a2), swap(m1, m2);
    ll x, y, g = exGCD(m1, m2, x, y);
    if ((a1 - a2) % g != 0) return {0, -1}; // doesn't exist
    x = a1 + (__int128)(a2 - a1) % m2 * x % m2 / g * m1;
    if (x < 0) x += m1 / g * m2;
    return {x, m1 / g * m2};
}
