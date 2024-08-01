#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 1e8 + 1;

bitset<MAX> is_prime;
vector<int> primes;

void sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAX; i++) {
		if (is_prime[i]) primes.emplace_back(i);
		for (int p : primes) {
			if (i * p >= MAX) break;
			is_prime[i * p] = false;
			if (i % p == 0) break;
		}
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    sieve();



    return 0;
}
