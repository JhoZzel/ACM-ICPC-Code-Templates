#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e3 + 5;

bitset<N> is_prime;

void sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for (int i = 4; i < N; i += 2) is_prime[i] = false;
    for (int i = 3; i * i < N; i += 2) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j < N; j += i) {
            is_prime[j] = false;
        }
    }
}

int main() {
    sieve();
    for (int i = 1; i < N; i++) {
        cout << i << " " << (is_prime[i] ? "YES" : "NO") << "\n";
    }
    return 0;
}
