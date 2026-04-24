// Manacher
//

void manacher(vector<int> &s, vector<int> &d1, vector<int> &d2) {
    int n = s.size();

    d1.assign(n, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }

    d2.assign(n, 0); 
    for (int i = 0, l = 0, r = -1; i < n; i++) { // [i, i + 1]
        int k = (i > r) ? 0 : min(d2[l + r - i - 1], r - i);
        while (i - k >= 0 && i + 1 + k < n && s[i - k] == s[i + 1 + k]) k++;
        d2[i] = k--;
        if (i + 1 + k > r) l = i - k, r = i + 1 + k;
    }
}
