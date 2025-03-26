#include <bits/stdc++.h>
 
using namespace std;
 
const int LOG = 30;

int sz;
int B[LOG];

void insert(int mask) {
    for (int i = 0; i < LOG; i++) {
		if ((mask & 1 << i) == 0) continue;
        if (!B[i]) {
            B[i] = mask;
            sz++;
            return;
        }
        mask ^= B[i];
    }
}

void clean() {
    sz = 0;
    memset(B, 0, sizeof(B));
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        int d,m;
        cin >> d >> m;
        for (int i = 0; i < m; i++) {
            int x; cin >> x;
            insert(x);
        }
        cout << (1 << (d - sz)) << '\n';
        clean();
    }
	return 0;
}

// https://www.codechef.com/problems/XORCMPNT
