#include <bits/stdc++.h>
#define dbg(x) cerr << #x << " = " << x << endl
#define raya cerr << string(15, '=') << endl
#define ff first
#define ss second
using namespace std;
typedef long long ll;

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
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, L; 
    cin >> n >> L;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    MAX_Queue r;
    for (int i = 0; i < n; i++) {
        r.add(a[i]);
        if (i < L - 1) continue;
        cout << r.query() << ' ';
        r.pop();
    }
    cout << '\n';
    return 0;
}
