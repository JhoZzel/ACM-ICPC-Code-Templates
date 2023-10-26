#include <bits/stdc++.h>
using namespace std;
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(c) (c).begin(), (c).end()
#define rall(A) A.rbegin(), A.rend()
#define pb push_back
#define dbg(x) do {cerr << #x << " = " << (x) << "\n";} while(false)
#define f first
#define s second

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int q; cin >> q;

    string ans = a[0];
    set<char> b;
    for (char e : ans) b.insert(e);

    while(q--) {
        int cnt = 0;
        string pat; cin >> pat;
        for (int i = 0; i < n; i++) {
            string cand = a[i];
            string p = ".....";
            for (int k = 0; k < 5; k++) {
                if (cand[k] == ans[k]) p[k] = '*';
                if (cand[k] != ans[k]) p[k] = 'X';
                if (b.count(cand[k]) and ans[k] != cand[k]) p[k] = '!';
            }
            cnt += (p == pat);
        }
        cout << cnt << "\n";
    }
    return 0;
}