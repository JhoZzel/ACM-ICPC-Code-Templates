#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e7 + 5;

bitset<N> composite;

void sieve() {
    composite[1] = true;
    for (int i = 4; i < N; i += 2) composite[i] = true;
    for (int i = 3; i < N; i += 2) {
        if (composite[i]) continue;
        for (ll j = 1ll * i * i; j < N; j += i) {
            composite[j] = true;
        }
    }
}

int main() {
    sieve();
    for (int i=1; i<N; i++) {
        cout << i << " " << (composite[i] ? "NO" : "YES") << "\n";
    }
    return 0;
}
