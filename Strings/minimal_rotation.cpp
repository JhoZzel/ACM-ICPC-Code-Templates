string minimal_rotation(string s) { // O(n)
	int n = s.length();
	s += s;
	int i = 0, j = 1;
	while (i < n and j < n) {
		int k = 0;
		while (k < n and s[i + k] == s[j + k]) k++;

		if (s[i + k] <= s[j + k]) j += k + 1;
		else i += k + 1;

		if (i == j) j++;
	}
	int start = min(i, j);
	return s.substr(start, n);
}
