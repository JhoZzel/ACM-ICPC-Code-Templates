#include <bits/stdc++.h>
using namespace std;

#define x real()
#define y imag()

using ll = long long;
using pt = complex<ll>;

ll cross(pt a, pt b) { return imag(conj(a) * b); }

pt read() {
    int p,q;
    cin >> p >> q;
    return pt(p, q);
}

vector<pt> convex_hull(vector<pt> a) { // include colinear
    const int n = a.size();
    if (n == 1) return a;
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (make_pair(a[i].y, a[i].x) < make_pair(a[idx].y, a[idx].x)) {
            idx = i;
        }
    }

    pt p0 = a[idx];
    
    a.erase(a.begin() + idx);
    sort(a.begin(), a.end(), [&](pt A, pt B) {
        int o = cross(A - p0, B - p0);
        if (o == 0) return norm(A - p0) < norm(B - p0);
        return o > 0;
    });
    a.insert(a.begin(), p0);

    // if a is a line the order is reverted

    // last line edge case
    int j = n - 2;
    while(j >= 0 and cross(a[n - 1] - p0, a[j] - p0) == 0) {
        j--;
    }
    reverse(a.begin() + j + 1, a.end());

    // building convex hull
    vector<pt> st = {a[0], a[1]};
    for (int i = 2; i < n; i++) {
        pt B = a[i];
        while(true) {
            pt A = st.back(); st.pop_back();
            pt C = st.back();
            if (cross(B - A, C - A) >= 0) {
                st.push_back(A);
                st.push_back(B);
                break;
            }
        }
    }

    return st;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<pt> a(n);
    for (int i = 0; i < n; i++) a[i] = read();
    vector<pt> ch = convex_hull(a);
    cout << ch.size() << '\n';
    for (auto p : ch) {
        cout << p.x << " " << p.y << '\n';
    }
    return 0;
}
