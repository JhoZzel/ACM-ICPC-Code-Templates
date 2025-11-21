// Convex Hull
//

#define x real()
#define y imag()

using ll = long long;
using pt = complex<ll>;

ll dot(pt a, pt b) { return real(conj(a) * b); }
ll cross(pt a, pt b) { return imag(conj(a) * b); }

pt read() {
    int p,q;
    cin >> p >> q;
    return pt(p, q);
}

vector<pt> convex_hull(vector<pt> a) { // no include colinear
    const int n = a.size();
    if (n <= 2) return a;
    
    for (int i = 1; i < n; i++) {
        if (make_pair(a[i].x, a[i].y) < make_pair(a[0].x, a[0].y)) {
            swap(a[i], a[0]);
        } 
    }

    sort(a.begin() + 1, a.end(), [&](pt A, pt B) {
        pt p0 = a[0];
        ll v = cross(A - p0, B - p0);
        if (v == 0) return norm(A - p0) < norm(B - p0);
        return v > 0;
    });

    vector<pt> st;
    st.push_back(a[0]);
    for (int i = 1; i < n; i++) {
        while(st.size() >= 2) {
            pt A = a[i];
            pt B = st.back(); st.pop_back();
            pt C = st.back();
            if (cross(A - B, C - B) > 0) {
                st.push_back(B);  
                break;
            } 
        }
        st.push_back(a[i]);
    }

    return st;
}
