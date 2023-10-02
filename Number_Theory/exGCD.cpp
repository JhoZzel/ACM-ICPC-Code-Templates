#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll exGCD(ll a, ll b, ll &x_0, ll &y_0) {
    if (b == 0) { 
        x_0 = 1;
        y_0 = 0;
        return a;
    }  
    ll x_1, y_1;
    ll g = exGCD(b, a % b, x_1, y_1);
    x_0 = y_1;
    y_0 = x_1 - (a / b) * y_1;
    return g;
}

int main() {
    int n1 = 132;
    int n2 = 814;
    ll x,y;
    ll d = exGCD(n1,n2,x,y);
    cout << "d : " << d << endl;
    cout << "x : " << x << endl;
    cout << "y : " << y << endl;
    return 0;
}
