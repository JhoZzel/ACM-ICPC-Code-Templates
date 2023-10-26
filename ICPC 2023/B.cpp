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
    int n; cin >> n;
    
    vector<int> a(3*n);
    map<int,int> ma;
    for (int i = 0; i < 3* n; i++) {
        cin >> a[i];
        ma[a[i]]++;
    }
    ll sa = 0;
    bool ok = 1;
    for (auto e : ma) {
        if (e.second % 3 != 0) ok = 0;
    }

    cout << (ok ? "N" : "Y") << "\n";


    return 0;
}