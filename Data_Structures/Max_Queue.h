struct MAX_Queue {
    deque<int> dq;
    
    MAX_Queue() {}

    void push(int x) {
        while(!dq.empty() and x > dq.back()) {
            dq.pop_back();
        }
        dq.push_back(x);
    }
    void pop(int x) {
        assert(!dq.empty());
        if (dq.front() == x) dq.pop_front();
    }
    int query() {
        assert(!dq.empty());
        return dq.front();
    }
};
