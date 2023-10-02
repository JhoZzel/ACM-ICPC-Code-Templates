#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.end()
#define pb push_back
#define pf push_front
#define PI acos(-1)
#define F first
#define S second

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef vector<string> vs;
typedef priority_queue<int> pq_max;
typedef priority_queue<int, vi, greater<int>> pq_min;

const int maxn = 2e5;
const u32 MOD = 1000000007;

bool is_prime[2e9];

bool isComposite(u64 n, u64 a, u64 d, int s);
bool millerRabin(u64 n);
u64 power(ll x,int n);
u64 modPower(u64 x,u64 n, u64 mod);
u64 binpower(u64 base, u64 e, u64 mod);
u64 modInverse(u64 x, u64 mod);
void sieveEratosthenes();

int main(){ 
    // code here
    
    return 0;
}


void sieveEratosthenes() {
    memset(is_prime, 1, maxn);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= maxn; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= maxn; j += i)
                is_prime[j] = 0;
        }
    }
}

bool isComposite(u64 n, u64 a, u64 d, int s) {
    u64 x = modPower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool millerRabin(u64 n) { // n<2^63-1 n:64bits LL
    if (n < 2)
        return false;

    int s = 0;
    u64 d = n - 1;
    while (d % 2 == 0) {
        d/=2;
        s++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (isComposite(n, a, d, s))
            return false;
    }
    return true;
}

/*
bool MillerRabin(u64 n, int iter=5) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    // n-1 = 2^s.d
    int s = 0;
    u64 d = n - 1;
    while (d % 2 == 0) {
        d/=2;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3); // [0,n-2]
        if (isComposite(n, a, d, s))
            return false;
    }
    return true;
}*/

u64 power(u64 base, int n) {
    u64 result=1;
    while(n > 0) {
        if(n & 1)
            result *= base;
        base *= base;
        n >>= 1;
    }
    return result;
}

u64 modInverse(u64 x, u64 mod) {
    return modPower(x, mod-2, mod);
}

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}
