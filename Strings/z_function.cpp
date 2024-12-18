#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string& s) {
    const int n = (int) s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    vector<int> z = z_function(s);
    for (int e : z) cout << e << ' '; 
    return 0;
}

