#include <bits/stdc++.h>
using namespace std;

const int N = 8;

bool validate(int ni, vector<int> &Q) {
    int nj = Q.size();
    for (int j = 0; j < nj; j++) {
        if (Q[j] == ni) return 0;
        if (abs(Q[j] - ni) == abs(j - nj)) return 0;
    }
    return 1;
}

void print_table(vector<int> &Q) {
    vector<string> tab(N, string(N, '.'));
    for (int j = 0; j < (int)Q.size(); j++) {   
        tab[Q[j]][j] = 'Q';
    }
    for (int i = 0; i < N; i++) cout << "  " +  tab[i] << "\n";
    cout << "*" + string(10, '=') + "*" << "\n";
}

int back(vector<int> &Q) {
    if (Q.size() == N) {
        print_table(Q);
        return 1;
    }
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (validate(i,Q)) {
            Q.push_back(i);
            cnt += back(Q);
            Q.pop_back();
        }
    }
    return cnt;
}

int main() {
    vector<int> Q;
    int n_sol = back(Q);
    cout << "Number of soltions : " << n_sol << "\n";
    return 0;
 }
