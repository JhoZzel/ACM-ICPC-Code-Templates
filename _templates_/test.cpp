#include<bits/stdc++.h>
using namespace std;

#define sz(x) (int) x.size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define eb emplace_back
#define ff first
#define ss second

// Bitwise ops
#define bcnt __builtin_popcountll
#define bclz __builtin_clzll
#define max_bit(x) 31-__builtin_clz(x) // be careful with "x = 0"
#define max_bitll(x) 63 - __builtin_clzll(x)

using ll = long long;
using ull = unsigned long long;
using u128 = __uint128_t;

using pii = pair<int, int>;
using pq_max = priority_queue<int>;
using pq_min = priority_queue<int, vi, greater<int>>;

/// Debug
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> 
void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "): ", dbg_out(__VA_ARGS__)

//#define dbg(x) cerr << #x << " = " << x << endl
#define pv(x) cerr << #x << "[]: "; for (auto e : x) cerr << e << " "; cerr << endl
#define pv2(x) cerr << #x << endl; for (auto [a,b] : x) cerr << a << " " << b endl; cerr << endl
#define raya cerr << string(20, '=') << endl



const int N = 1e6 + 5;
const int MOD = 1e9  + 7;
const int INF = 1e9 + 9;
const ll INF_LL = 1e18 + 5;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return 1ll * a * b % MOD; }
int bpow(int a, ll e) {
    int r = 1;
    while(e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}
int inv(int a) { return bpow(a, MOD - 2); }




int main() {
 


    return 0;
}
