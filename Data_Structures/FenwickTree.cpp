#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;

struct FenwickTree {
    int N;
    vector<int> FT;
    FenwickTree(int n): N(n + 5), FT(n + 5) {}
    void update(int i, int x) {
        for (; i < N; i += i & -i) FT[i] += x;
    }
    int sum(int i) {
        int sa = 0;
        for (; i > 0; i -= i & -i) sa += FT[i];
        return sa;
    }
    int query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int main() {
    int n;
    cin >> n;
    FenwickTree FT(n);
    

    return 0;
}
