#include <bits/stdc++.h>
using namespace std;

bool p(int x) {
    cout << x << endl;
    int r;
    cin >> r;
    return r;
}

bool p(double x, vector<int>& a) {
    vector<double> sa(a.size() + 1);
    sa[0] = 0;
    for (int i=0; i<a.size(); ++i) {
        sa[i+1] = sa[i] + a[i];
    }
    //s[r] = sa[r] - r * x
    double min = 0;
    for (int i = k-1; i < a.size(); ++i) {
        if (sa[i] - i * x >= min) return 1;
        min = min(min, sa[i-k+1] - (i-k+1) * x);
    }
    return 0;
}


int main() {
    
    /**
     * predicado: 
     *  
     * 23.03240203443 no es un numero natural.
     * 100...004 no es un numero natural.
     * 
     * 
     * f(1) es verdad
     * f(n) -> f(n-1)
     * 
     * !f(n) -> !f(n+1)
     * 
     * 
     * 1, 1, 1, ..., 1, [0, 0, ..., 0 ..)
     * 1, 1, 1, ..., 1, ..... 1 ...
     * 
     * [1, 1, ..., 1]
     * [0, 0, ..., 0]
     * [1, 1, 1, 0, ..., 0]
     * 
     */

    //7

    //si el numero que dices es mayor al que estoy pensando te dire que es mayor.
    //En otro caso, te dire que es igual o menor o igual.

    

    //lo ->       lo                   hi
    //[1 1 1 1 1] 1 1 1 1 0 0 ]0 0 0 0 0 0
    //                  x

    int lo = 1, hi = 100;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (p(mid)) lo = mid; 
        else hi = mid-1;
    }
    //[1 0], [0, 0], [1, 1]

    int lo = 1, hi = 100;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (p(mid)) lo = mid+1; 
        else hi = mid;
    }

    //lo = hi
    cout << lo << endl;

    //a1, a2, ..., an
    //(al, al+1, al+2, ar) 
    //k >= r - l + 1 
    // max (al + al+1 + al+2 + ... ar) / (r - l + 1)

    //p(x): el maximo promedio es >= x

    /**
     * (al + al+1 + al+2 + ... ar) - x * (r - l + 1) >= 0
     * (al-x + al+1-x + al+2-x + ... ar-x) >= 0
     * sr - s(l-1) >= 0 
     * sr >= s(l-1) (r - l + 1 >= k)
     */
    //x [x + e]
    double lo = -1e8, hi = 1e8;
    while (lo < hi) {
        double mid = (lo + hi) / 2;
        if (p(mid)) lo = mid+1; 
        else hi = mid;
    }

    //e = 10^-7
    //[hi - lo] / e -> 2x10^8 x 10^7 = 2x10^15 <= 2 x (2^10)^5 = 2^51
    double lo = -1e8, hi = 1e8;
    for (int i = 0; i < 51; ++i) {
        double mid = (lo + hi) / 2;
        if (p(mid)) lo = mid+1; 
        else hi = mid;
    }
    cout << lo << endl;

    return 0;
}