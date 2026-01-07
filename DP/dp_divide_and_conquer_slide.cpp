// DP Divide and Conquer (slide)
// 

using ll = long long;

const int INF = 1e9;
const int N = 3.5e4 + 5;

int n,K,L,R;
int a[N];
int freq[N];
int dp[N][2];
int cost;

int query(int l, int r) {
    while(R < r) {
        R++;
        if(freq[a[R]] == 0) cost++;
        freq[a[R]]++;
    }
    while(L > l) {
        L--;
        if(freq[a[L]] == 0) cost++;
        freq[a[L]]++;
    }
    while(R > r) {
        freq[a[R]]--;
        if(freq[a[R]] == 0) cost--;
        R--;
    }
    while(L < l) {
        freq[a[L]]--;
        if(freq[a[L]] == 0) cost--;
        L++;
    }
    return cost;
}


void go(int l, int r, int id, int opl = 1, int opr = n) {
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<int, int> mx = {-INF, mid};

    for (int j = opl; j <= min(opr, mid); j++) {
        mx = max(mx, pair{dp[j - 1][id ^ 1] + query(j, mid), j});
    }

    int opt = mx.second;
    dp[mid][id] = mx.first;

    go(l, mid - 1, id, opl, opt);
    go(mid + 1, r, id, opt, opr);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cin >> n >> K;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    L = 1, R = 0;
    for (int k = 1; k <= K; k++) {
        go(1, n, k & 1);
    }
    
    cout << dp[n][K & 1] << "\n";

    return 0;
}
