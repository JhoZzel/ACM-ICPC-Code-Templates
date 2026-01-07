// Topological order
//

vector<int> top_order() {
    vector<int> order;
    queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (in[i]) continue;
        Q.push(i);
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int w : ady[u]) {
            if (--in[w] == 0) Q.push(w);
        }
        order.push_back(u);
    }
    return ((int)order.size() < n) ? vector<int>() : order;
}
