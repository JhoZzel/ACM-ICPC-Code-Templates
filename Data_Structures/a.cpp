#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define dbg(x) do {cerr << #x <<" = " << (x) << endl; } while (false)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int) x.size())
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll,ll> pll;
typedef vector<ii> vii;
typedef vector<pll> vll;

const int N = 1e5 + 5;
const int LOG = 17;

template<class T>
struct ST {
    T jmp[N][LOG];

    ST(const vector<T>& A) {
        int n = A.size();
        for(int i = 0; i < n; i++) jmp[i][0] = A[i];
        for(int d = 1, p = 1; 2 * p <= n; d++, p <<= 1) {
            for(int i = 0; i + 2 * p - 1 < n; i++) {
                jmp[i][d] = gcd(jmp[i][d - 1], jmp[i + p][d - 1]);
            }
        }
    }

    T query(int l, int r) { // [l,r]
        int d = r - l + 1;
        int k = 31 - __builtin_clz(d); 
        return gcd(jmp[l][k], jmp[r - (1 << k) + 1][k]);
    }
};

int main() {
    int n; 
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    ST<int> st(a);
    for (int i = 0; i < n; i++) {
        cout << st.query(0,i) << "\n";
    }
    int q; cin >> q;
    while(q--) {
        int x; cin >> x;    
    }
    return 0;
}
