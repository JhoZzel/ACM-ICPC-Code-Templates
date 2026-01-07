// RMQ O(1)
// 

struct SparseTable {
    vector<vector<int>> st;

    SparseTable() {}

    SparseTable(vector<int> &a) { // 0-indexed
        int n = a.size();
        int k = __lg(n) + 1;
        st.resize(n, vector<int>(k));
        for (int i = 0; i < n; i++) st[i][0] = a[i];
        for (int p = 1, d = 1; 2 * d <= n; p++, d <<= 1) {
            for (int i = 0; i + 2 * d <= n; i++) {
                st[i][p] = min(st[i][p - 1], st[i + d][p - 1]);
            }
        }
    }
    
    int query(int l, int r) {
        if (l > r) return INT_MAX;
        int k = __lg(r - l + 1);
        int d = (1 << k);
        return min(st[l][k], st[r - d + 1][k]);
    }
};

struct RMQ {
    int n,k;
    SparseTable st;
    vector<int> a,b,id;
    vector<vector<int>> masks;

    RMQ (vector<int> &a) : a(a) {
        n = a.size();
        k = max(1, __lg(n));

        id.resize(n);

        for (int i = 0; i < n; i += k) {
            int mask = 0;
            int mn = INT_MAX;
            stack<int> st;
            vector<int> stack_mask;
            for (int j = i; j < min(i + k, n); j++) {
                id[j] = i / k;
                mn = min(mn, a[j]);
                while(!st.empty() and a[j] <= a[st.top() + i]) {
                    mask ^= 1 << st.top();
                    st.pop();
                }
                mask ^= 1 << (j - i);
                st.push(j - i);
                stack_mask.push_back(mask);
            }
            b.push_back(mn);
            masks.push_back(stack_mask);
        }

        st = SparseTable(b);
    }


    int query_block(int l, int r, int me) { 
        int off = me * k;
        int m = masks[me][r] >> l;
        int pos = __lg(m & -m) + l;
        return a[pos + off];
    }

    int query(int l, int r) {
        int id_l = id[l], id_r = id[r];
        if (id_l == id_r) {
            int s = id_l * k;
            l -= s; r -= s;
            return query_block(l, r, id_l);
        }
        else {
            int mn = st.query(id_l + 1, id_r - 1);
            int s1 = id_l * k, s2 = id_r * k;
            l -= s1; r -= s2;
            mn = min(mn, query_block(l, k - 1, id_l));
            mn = min(mn, query_block(0, r, id_r));
            return mn;
        }
    }
};
