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

const int N = 2e5 + 5;
const int LOG = 18;

template<class T>
struct ST {
    T jmp[N][LOG];

    ST(const vector<T>& A) {
        int n = A.size();
        for(int i = 0; i < n; i++) jmp[i][0] = A[i];
        for(int d = 1, p = 1; 2 * p <= n; d++, p <<= 1) {
            for(int i = 0; i + 2 * p - 1 < n; i++) {
                jmp[i][d] = min(jmp[i][d - 1], jmp[i + p][d - 1]);
            }
        }
    }

    T query(int l, int r) {
        int d = r - l + 1;
        int k = 31 - __builtin_clz(d); 
        return min(jmp[l][k], jmp[r - (1 << k) + 1][k]);
    }
    
    T at(int pos) {
        return query(pos,pos);
    }
};

int main() {
    int n; 
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int q; cin >> q;
    ST<int> st(a);
    while(q--) {
        int l,r;
        cin >> l >> r;
        cout << st.query(l,r-1) << "\n";
    }
    return 0;
}
