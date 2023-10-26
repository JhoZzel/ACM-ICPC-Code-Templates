#include <bits/stdc++.h>
using namespace std;
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(c) (c).begin(), (c).end()
#define rall(A) A.rbegin(), A.rend()
#define pb push_back
#define dbg(x) do {cerr << #x << " = " << (x) << "\n";} while(false)
#define f first
#define s second

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll INV2 = 500000004;

typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;

int main() {
    string alp = "abcdefghijklmnopqrstuvwxyz";
    string s;
    ll n;
    cin >> s >> n;
    int len = s.length();
    vector<vector<ll>> suf(30,vi(len+1,0));

    for (char c = 'a'; c <= 'z'; c++) {
        int v = c - 'a';
        suf[v][len-1] = 0;
        for (int i = len - 2; i >= 0; i--) {
            suf[v][i] = (suf[v][i+1] + (s[i+1] < c)) % MOD;
        }
    }
    ll ans = 0, D = 0, T = 0;
    for (int i = 0; i < len; i++) {
        int v = s[i] - 'a';
        D = (D + suf[v][i]) % MOD;
        T = (T + suf[v][0] + (s[0] < s[i])) % MOD;
        //ans += (n % MOD) * (D % MOD) + (suf[v][0] + (s[0] < s[i])) * (n * (n - 1)) / 2;
    }
    n = n % MOD;
    ll s1 = (D * n) % MOD;
    ll s2 = (T * n) % MOD;
    s2 = (s2 * (n-1)) % MOD;
    s2 = (s2 * INV2) % MOD;
    ans = (s1 + s2) % MOD;

    cout << ans % MOD << "\n";
    return 0;
}