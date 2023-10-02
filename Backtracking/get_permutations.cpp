#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

void get_permutations(vvi &P, vi v, vb is_used, int n) {   
    if (v.size() == n) {
        P.push_back(v);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!is_used[i]) {
            v.push_back(i);
            is_used[i] = 1;
            
            get_permutations(P, v, is_used, n);
            
            is_used[i] = 0;
            v.pop_back();
        }
    }
}

int main() {
    int n; cin >> n;
    vvi permutations;
    get_permutations(permutations, {}, vb(n + 1, 0), n);
    
    for (vi v : permutations) {
        for (int e : v) cout << e << " ";
        cout << endl;
    }
    return 0;
}

