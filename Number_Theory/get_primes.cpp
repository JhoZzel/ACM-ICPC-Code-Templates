#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e8 + 1;

bitset<N> composite;

/*
    Linear Sieve:
    Compute all the primes up to N, also mark the 
    composite number
*/

vector<int> get_primes() {
	vector<int> primes;
    for(int i = 2; i < N; i++) {
		if(not composite[i]) primes.emplace_back(i);
		for(int p : primes) {
			if(i * p >= N) break;
			composite[i * p] = true;
			if(i % p == 0) break;
		}
	}
    return primes;
}

int main() {
    vector<int> p = get_primes();
    for (int e : p) 
        cout << e << "\n";
    return 0;
}
