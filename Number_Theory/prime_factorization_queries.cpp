#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

const int N = 1e7 + 5;

vector<int> SPF(N);

void get_SPF() { // O(nloglogn)
	SPF[1] = 1;
	for (int i = 2; i < N; i++) SPF[i] = i;
	for (int i = 4; i < N; i+=2) SPF[i] = 2;
	for (int i = 3; i * i < N; i += 2) {
		if (SPF[i] != i) continue;
        for (int j = i * i; j < N; j += i) {
            if (SPF[j] == j) {
                SPF[j] = i;
            } 
        }
    }
}

vii prime_factorization(int n) { // O(logn)
    vii PF;
    while (n != 1) {
        int p = SPF[n];
        int e = 0;
        while(n % p == 0) {
            e++;
            n /= p;
        }
        PF.emplace_back(p,e);
    }
    return PF;
}

int main() {
	fast_io;        
    get_SPF();
    int q; cin >> q;
    while(q--) {
        int n; cin >> n;
        vii p = prime_factorization(n);
        for (ii e : p) cout << e.F << " " << e.S << "\n";
        cout << "\n";
    }
	return 0;
}
