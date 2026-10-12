
void build_cartesian_tree() { // max above -- array a[N]  lengt = n
	memset(L,-1,sizeof L);
	memset(R,-1,sizeof R);	

	stack<int> st;
	for (int i = 0; i < n; i++) {
		int last = -1;
		while(!st.empty() and a[i] > a[st.top()]) {
			last = st.top();
			st.pop();
		}
		if (last != -1) L[i] = last;
		if (!st.empty()) R[st.top()] = i;
		st.push(i);
	}

	while(!st.empty()) {
		root = st.top();
		st.pop();
	}
}
