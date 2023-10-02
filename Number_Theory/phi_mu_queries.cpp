#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
using namespace std;

const int N = 1e7 + 5;

vector<int> SPF(N);

void get_SPF() {
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

void get_phi_mu(int n, int &phi, int &mu) {
    while (n != 1) {
        int p = SPF[n];
        phi -= phi/p;
        int e = 0;
        while(n % p == 0) {
            n /= p;
            e++;
        }
        if (e > 1) mu = 0;
        else mu = -mu;
    }
}

void solve() {
    int n; 
    cin >> n;
    int phi = n, mu = 1;
    get_phi_mu(n, phi, mu);
    cout << phi << " " << mu << "\n";
}

int main() {
	fast_io;        
    get_SPF();
    int q; cin >> q;
    while(q--) {
        solve();
    }
	return 0;
}
