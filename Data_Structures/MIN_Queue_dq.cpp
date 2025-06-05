#include <bits/stdc++.h>
using namespace std;

struct MIN_Queue {
    deque<int> dq;
    
    MIN_Queue() {}

    void push(int x) {
        while(!dq.empty() and x < dq.back()) {
            dq.pop_back();
        }
        dq.push_back(x);
    }
    void pop(int x) {
        if (dq.front() == x) {
            dq.pop_front();
        }
    }
    int query() {
        return dq.front();
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n,k;
    cin >> n >> k;

    int x,a,b,c;
    cin >> x >> a >> b >> c;

    vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(x);
        x = (1ll * a * x + b) % c;
    }
    
    int ans = 0;
    MIN_Queue mq;
    for (int i = 0; i < k - 1; i++) mq.push(v[i]);
    for (int i = k - 1; i < n; i++) {
        mq.push(v[i]);
        ans ^= mq.query();
        mq.pop(v[i - k + 1]);
    }
    cout << ans << "\n";

    return 0;
}

// https://cses.fi/problemset/result/13190108/
