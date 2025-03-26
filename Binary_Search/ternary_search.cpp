
double ternary_search(double l, double r) {
    double eps = 1e-6;          //set the error limit here
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) l = m1;
        else r = m2;
    }
    return f(l);     //return the maximum of f(x) in [l, r]
}

ll ternary_search(int lo, int hi) {
    while (hi - lo > 2) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) lo = m1;
        else hi = m2;
    }
    ll ans = 0;
    for (int i = lo; i <= hi; i++) {
        ans = max(ans, f(i));
    }
    return ans;       //return the maximum of f(x) in [l, r]
}
