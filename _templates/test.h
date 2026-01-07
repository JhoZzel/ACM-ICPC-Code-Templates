#include <bits/stdc++.h>
using namespace std;

#define raya cerr << string(20, '=') << endl 

using ll = long long;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

ll random(ll L, ll R) {
    return uniform_int_distribution<ll>(L, R)(rnd);
}

template <typename T>
void __print(const T &x) { cerr << x; }

template <typename T, typename U>
void __print(const pair<T, U> &x) { cerr << '('; __print(x.first); cerr << ", "; __print(x.second); cerr << ')'; }

template <typename T>
void __print(const vector<T> &v) { cerr << '{'; for (size_t i = 0; i < v.size(); ++i) { if (i) cerr << ", "; __print(v[i]); } cerr << '}'; }

template <typename T>
void __print(const set<T> &v) { cerr << '{'; for (auto it = v.begin(); it != v.end(); ++it) { if (it != v.begin()) cerr << ", "; __print(*it); } cerr << '}'; }

template <typename T, typename U>
void __print(const map<T, U> &v) { cerr << '{'; for (auto it = v.begin(); it != v.end(); ++it) { if (it != v.begin()) cerr << ", "; __print(*it); } cerr << '}'; }


template <typename T>
void __print(queue<T> q) {
    cerr << '{';
    while (!q.empty()) {
        __print(q.front());
        q.pop();
        if (!q.empty()) cerr << ", ";
    }
    cerr << '}';
}

template <typename T>
void __print(stack<T> s) {
    cerr << '{';
    while (!s.empty()) {
        cerr << s.top();
        s.pop();
        if (!s.empty()) cerr << ", ";
    }
    cerr << '}';
}

template<typename T, size_t N>
void pa(const T (&a)[N]) {
    cerr << "-> ";
    for (size_t i = 0; i < N; i++) cerr << a[i] << " ";
    cerr << "\n";
}

void _dbg() { cerr << endl; }

template <typename T, typename... Args>
void _dbg(T a, Args... args) { __print(a); cerr << " "; _dbg(args...); }

#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: ", _dbg(__VA_ARGS__)

