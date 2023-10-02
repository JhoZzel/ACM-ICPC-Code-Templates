#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

/*
    Generate all subsets (2^n) given a n   
*/

void gen_subsets(vvi &ss, vi v, int n) {
    int aux = 0;
    if (v.size()!=0) aux = v.back();
    for (int i = aux + 1; i <= n; i++) {
        v.push_back(i);
        ss.push_back(v); 
        gen_subsets(ss, v, n);
        v.pop_back();
    }
}

int main() {
    int n; cin >> n;
    vvi ss;
    gen_subsets(ss,{},n);
    for (vi v : ss) {
        for (int e : v) cout << e << " ";
        cout << endl;
    }
    return 0;
}

