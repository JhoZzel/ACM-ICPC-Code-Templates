#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_V = 1e7 + 5;

int big[MAX_V];

void sieve() {
    for (int i = 2; i < MAX_V; i++) {
        if (big[i]) continue;
        for (int j = i; j < MAX_V; j += i) {
            big[j] = i;
        }
    }
}

vector<int> fact(int n) {
    vector<int> v;
    int p = big[n];
    while(n != 1) {
        while(n % p == 0) {
            v.emplace_back(p);
            n /= p;
        }
        p = big[n];
    }
    return v;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    sieve();
    
    int n;;
    while(cin >> n) {
        vector<int> f = fact(n);
        for (int e : f) cout << e << ' ';
        cout << '\n';
    }
    
    return 0; 
}
