#include <bits/stdc++.h>
using namespace std;
int main() {
    int a[] = {1,2,3,3,6,7,9,9,10};
    int n = sizeof(a)/sizeof(int);

    int lo = 1, hi = n-1, target = 6;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (a[mid] >= target) hi = mid;
        else lo = mid + 1;
    }
    cout << lo;

    return 0;
}