#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e8 + 5;

bitset<N> composite;

/*
 Given an integer n, compute the number of integer primes 
 less than or equal to n
*/

int count_primes(int n) {
    if (n == 2) return 1;
    int cnt = 1;
    composite[1] = true;
    for(int i = 3; i <= n; i += 2) {
        if(composite[i]) continue;
        for (ll j = 1ll * i * i; j <= n; j += i) {
            composite[j] = true;
        }
        cnt++;
    }
    return cnt;
}

int main() {
    int n = 72721621;
    cout << count_primes(n) << "\n";
    return 0;
}
