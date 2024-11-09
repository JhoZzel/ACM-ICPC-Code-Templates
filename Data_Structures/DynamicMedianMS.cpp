#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 9;

struct DynamicMedianMS {
    multiset<int> ms;
    multiset<int>::iterator med_it;
    int med_idx;
 
    DynamicMedianMS() : ms({-INF}), med_it(ms.begin()), med_idx(0) {}
  
    void insert(int x) {
        if(x < *med_it) med_idx++; // correct the index
        ms.insert(x);
        int idx = ms.size() / 2; // the index of real median
        if(med_idx < idx) med_it++;
        if(med_idx > idx) med_it--;
        med_idx = idx;
    }

    void remove(int x) {
        if (x <= *med_it) med_idx--; // correct the index
        if (ms.find(x) == med_it) {
            int idx = (ms.size() - 1) / 2;
            if (med_idx == idx) med_it--;
            else med_it++;
            med_idx = idx;
            ms.erase(ms.find(x));
            return;
        }
        ms.erase(ms.find(x));
        int idx = ms.size() / 2; // the index of real median
        if(med_idx < idx) med_it++;
        if(med_idx > idx) med_it--;
        med_idx = idx;
    }
    
    int get() {
        return *med_it;
    }
};

int main() {
    DynamicMedianMS S;
    cout << "MEDIAN (0):\n";
    cout << "INSERT (1): x\n";
    cout << "REMOVE (2): x\n";
    while(true) {
        cout << "ms[]: ";
        for (int e : S.ms) cout << e << " ";
        cout << endl;
        int op; cin >> op;
        if (op == 0) cout << S.get() << '\n';
        else {
            int x; cin >> x;
            if (op == 1) S.insert(x);
            else S.remove(x);
        }
    }
}
