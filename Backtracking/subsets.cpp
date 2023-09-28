#include <bits/stdc++.h>
using namespace std;

void printVector(vector<int> v) {
    for (int e : v) 
        cout << e << " ";
}

void back(vector<int> v, int n) {
    int aux = 0;
    if (v.size()!=0) aux = v.back();
    
    for (int i = aux + 1; i <= n; i++) {
        printVector(v);
        cout << i << "\n";
        v.push_back(i);
        back(v, n);
        v.pop_back();
    }
}

int main() {
    int n; cin >> n;
    back({},n);
    return 0;
}