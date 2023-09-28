#include <iostream>
using namespace std;
int main() {
    // FORMA 1 0
    bool p[] = {1,1,1,0,0,0,0,0,0};
    int n = sizeof(p) / sizeof(bool);


    // PRIMER "0"
    int lo = 1, hi = n-1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (p[mid]) lo = mid+1; 
        else hi = mid;
    }

    cout << lo << endl;

    // ULTIMO "1"
    lo = 1, hi = n-1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (p[mid]) lo = mid; 
        else hi = mid-1;
    }
    
    cout << lo << endl;

    return 0;
}