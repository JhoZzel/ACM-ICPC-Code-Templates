#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;
using Poly = vector<ll>;

const int MOD = 1e9 + 7;

ll bpow(ll a, ll e) {
    ll r = 1;
    while(e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    } 
    return r;
}

struct BerlekampMassey {
    Poly berlekamp_massey(Poly &s) { 
        int n = sz(s), L = 0, m = 0;
        Poly C(n, 0), B(n, 0), T;
        C[0] = 1; B[0] = 1;

        ll b = 1;
        for (int i = 0; i < n; i++) {
            m++;
            ll d = s[i]; //s => [0, MOD>
            for (int j = 1; j <= L; j++) d = (d + C[j] * s[i - j]) % MOD;
            if (d == 0) continue;
            T = C;
            ll c = d * bpow(b, MOD - 2) % MOD;
            for (int j = m; j < n; j++) C[j] = (C[j] - c * B[j - m]) % MOD;
            if (2 * L > i) continue;
            L = i + 1 - L, B = T, b = d, m = 0;
        }

        C.resize(L + 1);
        C.erase(C.begin());

        for (ll &x : C) x = (MOD - x) % MOD;

        return C;
    }

    ll linear_recurrence(Poly& a, Poly& tr, ll k) {
        int n = sz(tr);
        if (k < sz(a)) return a[k];

        auto combine = [&](Poly a, Poly b) {
            Poly res(2 * n + 1, 0);
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    res[i + j] += a[i] * b[j];
                    res[i + j] %= MOD;
                }
            }
            for (int i = 2 * n; i > n; i--) {
                for (int j = 0; j < n; j++) {
                    res[i - 1 - j] += res[i] * tr[j];
                    res[i - 1 - j] %= MOD;
                }
            }
            res.resize(n + 1);
            return res;
        };

        Poly pol(n + 1, 0), e(n + 1, 0);
        pol[0] = 1;
        e[1] = 1;
        
        k++;
        while (k > 0) {
            if (k & 1) pol = combine(pol, e);
            e = combine(e, e);
            k >>= 1;
        }

        ll res = 0;
        for (int i = 0; i < n; i++) {
            res += pol[i + 1] * a[i];
            res %= MOD;
        }
        return res;
    }

    ll run(Poly &a, ll k) { // 0-indexed
        if (k < sz(a)) return a[k];
        Poly tr = berlekamp_massey(a); 
        int L = sz(tr); // orden de la recurrencia minima
        if (L == 0) return 0; // {0, 0, 0, 0}
        return linear_recurrence(a, tr, k);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    ll n,k;
    cin >> n >> k;

    BerlekampMassey solver;

    int m = 4 * k + 6; // orden de la recursion

    vector<ll> F(m), A(m), S(m);

    F[0] = 1;
    F[1] = 2;

    for (int i = 2; i < m; i++) F[i] = (F[i - 1] + F[i - 2]) % MOD;
    for (int i = 0; i < m; i++) A[i] = F[i] * bpow(i + 1, k) % MOD;

    S[0] = A[0];
    for (int i = 1; i < m; i++) S[i] = (S[i - 1] + A[i]) % MOD;

    // get n-nth termino
    cout << solver.run(S, n - 1) << '\n';

    return 0;
}

