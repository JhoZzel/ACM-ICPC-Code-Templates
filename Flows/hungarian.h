// Hungarian
//

using ll = long long;

#define all(x) x.begin(), x.end()

struct Hungarian {
	static const ll INF = 1e18; //for maximum set INF to 0, and negate costs
	
    int n;
	vector<int> L, R;
    vector<vector<ll>> cs;
    
    Hungarian(int N, int M) { // N workers / M tasks
        n = max(N, M);
        cs.assign(n, vector(n, 0ll));
        L.assign(n, -1);
        R.assign(n, -1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cs[i][j] = INF;
    }
    
    void set(int i, int j, ll w) {
        cs[i][j] = w;
    }
    
	ll assign(){
		int mat = 0;
        vector<ll> ds(n), u(n), v(n);
		vector<int> dad(n), son(n);
        
        for (int i = 0; i < n; i++) u[i] = *min_element(all(cs[i]));
        for (int j = 0; j < n; j++) {
            v[j] = cs[0][j] - u[0];
            for (int i = 1; i < n; i++) {
                v[j] = min(v[j], cs[i][j] - u[i]);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (R[j] == -1 and cs[i][j] - u[i] - v[j] == 0) {
                    L[i] = j;
                    R[j] = i;
                    mat++;
                    break;
                }
            }
        }
		
        while (mat < n){
            int s = 0, j = 0, i;
			while (L[s] != -1) s++;

            dad.assign(n, -1);
            son.assign(n, 0);

			for (int k = 0; k < n; k++){
				ds[k] = cs[s][k] - u[s] - v[k];
            }
			
            while (true){
				j = -1;
                for (int k = 0; k < n; k++) {
                    if (!son[k] and (j == -1 or ds[k] < ds[j])) j = k;
                }
				son[j] = 1;
				i = R[j];
                if (i == -1) break;
				for (int k = 0; k < n; k++){
					if (!son[k]){
						ll new_ds = ds[j] + cs[i][k] - u[i] - v[k];
						if (ds[k] > new_ds){
							ds[k] = new_ds;
							dad[k] = j;
						}
					}
				}
			}
            
            for (int k = 0; k < n; k++) {
                if (k != j and son[k]) {
                    ll w = ds[k] - ds[j];
                    v[k] += w;
                    u[R[k]] -= w;
                }
            }
			
            u[s] += ds[j];
			
            while (dad[j] >= 0){
				int d = dad[j];
				R[j] = R[d];
				L[R[j]] = j;
				j = d;
			}

			R[j] = s;
			L[s] = j;
			mat++;
		}

        ll ans = 0;
        for (int i = 0; i < n; i++) {
            if (L[i] != -1) ans += cs[i][L[i]];
        }

		return ans;
	}

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i + 1 << " " << L[i] + 1 << '\n';
        }
    }
};
