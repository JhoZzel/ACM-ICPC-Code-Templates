#include <bits/stdc++.h>
#define dbg(x) cerr << #x << " = " << x << endl
#define raya cerr << string(15, '=') << endl
#define F first
#define S second
using namespace std;
typedef long long ll;

struct MAX_Stack{
    stack<pair<int,int>> s1,s2;
    int query() {
        if (s1.empty() or s2.empty()) {
            return s1.empty() ? s2.top().S : s1.top().S;
        }
        return max(s1.top().S, s2.top().S);
    }
    void add(int x) {
        int mx = s1.empty() ? x : max(x, s1.top().S);
        s1.emplace(x, mx);
    }
    void remove() {
        if (s2.empty()) {
            while(!s1.empty()) {
                int e = s1.top().F;
                s1.pop();
                int mx = s2.empty() ? e : max(e, s2.top().S);
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
    MAX_Stack r;
    for (int i = 0; i < n; i++) {
        r.add(a[i]);
        if (i < L - 1) continue;
        cout << r.query() << ' ';
        r.remove();
    }
    cout << '\n';
    return 0;
}

