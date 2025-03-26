#include <bits/stdc++.h>
using namespace std;

vector<int> LPS(string &s) { 
    const int n = s.size();
    vector<int> lps(n);
    for (int i = 1; i < n; i++) {
        int j = lps[i - 1];
        while (j > 0 and s[i] != s[j])
            j = lps[j - 1];
        if (s[i] == s[j])
            j++;
        lps[i] = j;
    }
    return lps;
}

vector<int> z_function(string& s) {
    const int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n and s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string s; cin >> s;

    for (int i : LPS(s)) 
        cout << i << ' ';
    cout << '\n';

    for (int i : z_function(s)) 
        cout << i << ' ';
    cout << '\n';

    return 0;
}
