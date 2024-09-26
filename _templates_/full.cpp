#include<bits/stdc++.h>
using namespace std;

// Useful in vectors
#define sz(x) (int) x.size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define maxi(x) *max_element(all(x)
#define mini(x) *min_element(all(x)
#define sum(x) accumulate(all(x), 0ll)
#define pb push_back
#define eb emplace_back
#define F first
#define S second

typedef long long ll;
typedef long double db;

// Pairs
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<ll,ll> pl;
// Vectors
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;
typedef vector<pl> vll;
typedef vector<string> vs;
typedef vector<bool> vb;
// Matrix
typedef vector<vi> vvi;
typedef vector<vl> vvl;

typedef priority_queue<int> pq_max;
typedef priority_queue<int, vi, greater<int>> pq_min;

// Loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
//#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
//#define R0F(i, a) ROF(i, 0, a)
#define each(a, x) for (auto &a : x)

/// Debug
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> 
void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "): ", dbg_out(__VA_ARGS__)

#define raya cout << string(20, '=') << endl
#define print_i(x) cout << "-> " << #x << ": "; each(e,x) cout << e << " "; cout << endl
#define print_ii(x) cout << "-> " << #x << ": "; each(e,x) cout << "(" << e.F << "-" << e.S << ") "; cout << endl;
#define print_iii(x) cout << "-> " << #x << ": "; for (auto [u,v,w] : x) cout << "(" << u << "-" << v <<  "-" << w << ") "; cout << endl;

// Bitwise ops
#define bcnt __builtin_popcountll
#define bclz __builtin_clzll
#define max_bit(x) 31-__builtin_clz(x) // be careful with "x = 0"
#define max_bitll(x) 63 - __builtin_clzll(x)

// Binary Search
template <class T> int low_b(int t, T x) { return distance(x.begin(), lower_bound(all(x), t)); }
template <class T> int up_b(int t, T x) { return distance(x.begin(), upper_bound(all(x), t)); }
template <class T, class U, class V> ll bs_first0(T low, U up, V p) { // => 1 1 1 (0) 0 0
    ll lo = low, hi = up;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (p(mid)) lo = mid + 1; 
        else hi = mid;
    }
    return lo;
}
template <class T, class U, class V> ll bs_last1(T low, U up, V p) { // 1 1 1 1 (1) 0 0
    ll lo = low, hi = up;
    while (lo < hi) {
        T mid = (lo + hi + 1) / 2;
        if (p(mid)) lo = mid; 
        else hi = mid - 1;
    }
    return lo;
}

// Others
#define fsp(x,e) fixed << setprecision(e) << x
template <class T> T rev(T x) { reverse(all(x)); return x; }
template <class T> void rem_dup(vector<T> &v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }
using u128 = __uint128_t;
using u64  = uint64_t;
using ull  = unsigned long long;

// Read
template <class T> void read(T &x) {cin >> x;}
template <class T> void read(vector<T> &v);
template <class T1, class T2> void read(pair<T1, T2> &p);
template <class R, class... T> void read(R& r, T&... t){read(r); read(t...);};
template <class T> void read(vector<T> &v) {each(x,v) read(x);}
template <class T1, class T2> void read(pair<T1, T2> &p) {read(p.F, p.S);}
template <class T1, class T2, class T3> void read(tuple<T1, T2, T3> &t) { read(get<0>(t)); read(get<1>(t)); read(get<2>(t));}
template <class T1, class T2, class T3> void read(vector<tuple<T1, T2, T3>> &v) { each(x,v) read(x);}

const int N = 1e6 + 5;
const int MOD = 1e9  + 7;
const int INF = 2e9 + 5;
const ll INFLL = 1e18 + 5;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};


void solve() {
    int n; cin >> n;
    vi a(n); read(a);
    
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie (0); 
    cout.tie(0);

    int t = 1; 
    cin >> t;
    while(t--) {
        solve();
        //cout << solve() << "\n";
        //cout << (solve() ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
