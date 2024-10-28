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
#define ff first
#define ss second

using ll = long long;
using ull = unsigned long long;
using u128 = __uint128_t;

using Double = long double;

// Pairs
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using iii = tuple<int, int, int>;

// Vectors
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<iii>;
using vl = vector<ll>;
using vll = vector<pll>;

// Matrix
using vvi = vector<vi>;
using vvl = vector<vl>;

// Priority Queues
using pq_max = priority_queue<int>;
using pq_min = priority_queue<int, vi, greater<int>>;

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
//#define dbg(x) cerr << #x << " = " << x << endl
#define pv(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define pv2(x) cerr << #x << endl; for (auto [a,b] : x) cerr << a << " " << b endl; cerr << endl
#define raya cerr << string(20, '=') << endl

// Bitwise ops
#define bcnt __builtin_popcountll
#define bclz __builtin_clzll
#define max_bit(x) 31-__builtin_clz(x) // be careful with "x = 0"
#define max_bitll(x) 63 - __builtin_clzll(x)

// Others
template <class T> T rev(T x) { reverse(all(x)); return x; }
template <class T> void rem_dup(vector<T> &v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }

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
const int INF = 1e9 + 9;
const ll INF_LL = 1e18 + 5;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};


void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
