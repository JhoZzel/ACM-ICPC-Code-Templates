#include <iostream>
using namespace std;
int main() {
    // FORMA 0 1
    bool p[] = {0,0,0,0,0,0,1,1,1,1,1,1,1,1}; 
    int n = sizeof(p) / sizeof(bool);

    
    // PRIMER "1"
    int lo = 1, hi = n-1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (!p[mid]) lo = mid+1; 
        else hi = mid;
    }

    cout << lo << endl;

    // ULTIMO "0"
    lo = 1, hi = n-1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (!p[mid]) lo = mid; 
        else hi = mid-1;
    }
    
    cout << lo << endl;

    return 0;
}