#include <bits/stdc++.h>
using namespace std;

#define ff first
#define ss second

using ll = long long;

struct MAX_Queue{
    stack<pair<int,int>> s1,s2;
    int query() {
        if (s1.empty() or s2.empty()) {
            return s1.empty() ? s2.top().ss : s1.top().ss;
        }
        return max(s1.top().ss, s2.top().ss);
    }
    void add(int x) {
        int mx = s1.empty() ? x : max(x, s1.top().ss);
        s1.emplace(x, mx);
    }
    void pop() {
        if (s2.empty()) {
            while(!s1.empty()) {
                int e = s1.top().ff;
                s1.pop();
                int mx = s2.empty() ? e : max(e, s2.top().ss);
                s2.emplace(e, mx);
            }
        }
        s2.pop();
    }
    void clean() {
        while(!s1.empty()) s1.pop();
        while(!s2.empty()) s2.pop();
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, L; 
    cin >> n >> L;

    vector<int> a(n);
    for (int &e : a) cin >> e;

    MAX_Queue Q;
    for (int i = 0; i < n; i++) {
        Q.add(a[i]);
        if (i < L - 1) continue;
        cout << Q.query() << ' ';
        Q.pop();
    }
    cout << '\n';

    return 0;
}
