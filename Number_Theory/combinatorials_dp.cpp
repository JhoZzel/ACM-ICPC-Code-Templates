#include<bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;
const int MOD = 1e9 + 7;

int C[N + 5][N + 5];

void get_combinatorials() {
    C[0][0] = 1;
    for (int k = 1; k <= N; k++) {
        for (int r = 0; r <= k; r++) {
            C[k][r] = (C[k-1][r-1] + C[k-1][r]) % MOD;
        }
    }
}

int main() {
    get_combinatorials();
    cout << C[1000][12] << endl;
    return 0;
}
