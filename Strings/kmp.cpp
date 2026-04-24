// KMP
//

// Para cada i, lps[i] es la longitud máxima de un prefijo propio (no puede tomar todo) que también es sufijo del substring s[0..i].

vector<int> kmp(string &s) { 
    int n = s.size();
    vector<int> lps(n);
    for (int i = 1; i < n; i++) {
        int j = lps[i - 1];
        while (j > 0 and s[i] != s[j]) j = lps[j - 1];
        if (s[i] == s[j]) j++;
        lps[i] = j;
    }
    return lps;
}
