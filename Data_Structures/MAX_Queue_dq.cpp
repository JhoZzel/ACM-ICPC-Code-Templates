#include <bits/stdc++.h>
using namespace std;

struct MAX_Queue {
    queue<int> Q;
    deque<int> dq;
    
    MAX_Queue() {}

    void push(int x) {
        while(!dq.empty() and x > dq.back()) {
            dq.pop_back();
        }
        Q.push(x);
        dq.push_back(x);
    }
    void pop() {
        assert(!Q.empty());
        if (dq.front() == Q.front()) {
            dq.pop_front();
        }
        Q.pop();
    }
    int query() {
        assert(!dq.empty());
        return dq.front();
    }
};


int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int q; cin >> q;
    MAX_Queue mxq;
    while(q--) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x;
            mxq.push(x);
        } else if (op == 2) {
            mxq.pop();
        } else {
            cout << mxq.query() << "\n";
        }
    }

    return 0;
}

