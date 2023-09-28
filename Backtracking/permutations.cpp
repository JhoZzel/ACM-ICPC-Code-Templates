#include <bits/stdc++.h>
using namespace std;

const int n = 10;

void printVector(vector<int> v) {
    for (int e : v) 
        cout << e << " ";
}

void back(vector<int> v, vector<bool> is_used, int n) {   
    for (int i = 1; i <= n; i++) {
        if (!is_used[i]) {
            printVector(v);
            cout << i << "\n";
            
            v.push_back(i);
            is_used[i] = 1;
            
            back(v, is_used, n);

            is_used[i] = 0;
            v.pop_back();
        }
    }
}

int main() {
    int n; cin >> n;
    back({}, vector<bool>(n + 1,0), n);
    return 0;
}