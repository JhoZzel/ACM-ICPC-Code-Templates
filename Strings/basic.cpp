#include <bits/stdc++.h>
#define dbg(x) cout << #x << " = " << x << endl;
#define RAYA cout << string(10, '=') << endl;
#define sz(x) (int) x.size()
using namespace std;

string mini(string a, string b) {
    if (sz(a) < sz(b)) return a;
    if (sz(b) < sz(a)) return b;
    const int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) return a;
        if (b[i] < a[i]) return b;
    }
    return a;
}

string maxi(string a, string b) {
    if (sz(a) > sz(b)) return a;
    if (sz(b) > sz(a)) return b;
    const int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) return a;
        if (b[i] > a[i]) return b;
    }
    return a;
}

string add(string a, string b) {
    int len = max(sz(a), sz(b));
    a = string(len - sz(a), '0') + a;
    b = string(len - sz(b), '0') + b;
    string res = "";
    int carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        int r = a[i] + b[i] - 2 * '0' + carry;
        carry = r / 10;
        r %= 10;
        res.push_back(r + '0');
    }
    if (carry != 0) res.push_back(carry + '0');
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);




    return 0;
}

