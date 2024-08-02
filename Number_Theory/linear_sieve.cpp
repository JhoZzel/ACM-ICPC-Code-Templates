#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 1e7 + 1;

bitset<MAX_V> composite;
vector<int> primes;

void sieve() {
    composite[0] = composite[1] = true;
    for (int i = 2; i < MAX_V; i++) {
		if (!composite[i]) primes.emplace_back(i);
		for (int p : primes) {
			if (i * p >= MAX_V) break;
			composite[i * p] = true;
			if (i % p == 0) break;
		}
	}
}

int main() {
    
    sieve();
    
    cout << "We found " << primes.size() << " primes\n";
    cout << "First primes....\n";
    for (int i = 0; i < 100; i++) {
        cout << primes[i] << " ";
    }

    return 0; 
}
