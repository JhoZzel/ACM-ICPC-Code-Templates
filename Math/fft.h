#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;
using cd = complex<double>;

const double PI = acos(-1);

void fft(vector<cd> &a, bool inv) {
    const int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int b = (n >> 1);
        for (; j & b; b >>= 1) j ^= b;
        j ^= b;
        if (i < j) swap(a[i], a[j]);
    }

    vector<cd> root(2 * n);
    root[1] = cd(1, 0);
    for (int k = 2; k < n; k <<= 1) {
        double th = 2 * PI / (k << 1) * (inv ? -1 : 1);
        cd w(cos(th), sin(th));
        for (int i = (k >> 1); i < k; i++) {
            root[2 * i] = root[i];
            root[2 * i + 1] = root[i] * w;
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * root[j + len / 2];
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
            }
        }
    }
    if (inv) for (cd &x : a) x /= n;
}

vector<ll> multiply(vector<int> &a, vector<int> &b) {
    int n = 1;
    while(n < sz(a) + sz(b) - 1) n <<= 1;
    vector<cd> aa(n), bb(n);
    for (int i = 0; i < sz(a); i++) aa[i] = cd(a[i], 0);
    for (int i = 0; i < sz(b); i++) bb[i] = cd(b[i], 0);
    fft(aa, 0);
    fft(bb, 0);
    for (int i = 0; i < n; i++) aa[i] *= bb[i];
    fft(aa, 1);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = round(aa[i].real());
    }
    return c;
}


