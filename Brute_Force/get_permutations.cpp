#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

vvi get_permutations(int a, int b) {
    vvi P;
    vi idx(b - a + 1); // len_max = 10
    iota(all(idx),a);
    do {
        P.push_back(idx);
    } while( next_permutation(all(idx)));
    return P;
}

int main() {
    vvi p = get_permutations(7,12);
    for (vi v : p) {
        for (int e : v) cout << e << " ";
        cout << endl;
    }
    return 0;
}


