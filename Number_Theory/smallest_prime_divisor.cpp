#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 1e7 + 5;

int spf[MAX_V];

void sieve() { 
    iota(spf, spf + MAX_V, 0);
	for (int i = 2; i * i < MAX_V; i++) {
		if (spf[i] != i) continue;
        for (int j = i * i; j < MAX_V; j += i) {
            if (spf[j] == j) {
                spf[j] = i;
            } 
        }
    }
}

vector<int> fact(int n) {
    vector<int> v;
    int p = spf[n];
    while(n != 1) {
        while(n % p == 0) {
            v.emplace_back(p);
            n /= p;
        }
        p = spf[n];
    }
    return v;
}

int main() {
    
    sieve();
    
    int n;;
    while(cin >> n) {
        vector<int> f = fact(n);
        for (int e : f) cout << e << ' ';
        cout << '\n';
    }
    
    return 0; 
}
