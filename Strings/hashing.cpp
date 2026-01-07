// Hashing
//

struct Hashing {
    vector<ll> p, h;
    Hashing(string &s, int B) {
        const int n = s.size();
        p.resize(n + 1);
        h.resize(n + 1);
        p[0] = 1;
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] * B % MOD;
        for (int i = n - 1; i >= 0; i--) {
            h[i] = h[i + 1] * B + (s[i] - 'a' + 1);
            h[i] %= MOD;
        }
    } 
    ll query(int l, int r) { // 0-indexed
        int len = r - l + 1;
        ll hs = h[l] - h[r + 1] * p[len] % MOD + MOD;
        hs %= MOD;
        return hs;
    }
};

