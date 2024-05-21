#include <bits/stdc++.h>
#define dbg(x) cerr << " [ " << #x << " = " << x << " ]\n"
#define print_v(x) cerr << #x << "[]: "; for (auto e : x) cerr << e <<" "; cerr << '\n'
#define RAYA cerr << string(15,'=')
using namespace std;
typedef long long ll;

const int N = 1e6 + 5;

ll add(ll a, ll b, ll mod) { 
    return (a % mod + b % mod) % mod; 
}
ll mul(ll a, ll b, ll mod) { 
    return a % mod * b % mod;
}
ll bpow(ll a, ll e, ll mod) {
    a %= mod;
    ll r = 1;
    while(e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}
ll inv(ll a, mod) { 
    return bpow(a, mod - 2); 

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 


    return 0;
}
