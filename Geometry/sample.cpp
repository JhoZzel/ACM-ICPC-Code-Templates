#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define PI acos(-1)
#define F first
#define S second

using namespace std;
    
#include "Point.h"
#include "CircleIntersection.h"

typedef Point<double> P;

int main() {
    P a,b;
    double k = 2.5;
    double w = PI/2;

    cin >> a >> b;

    cout << "a : " << a << endl;
    cout << "b : " << b << endl << endl;
    cout << "Punto MIN : " << min(a,b) << endl; 
    cout << "Punto MAX : " << max(a,b) << endl;
    cout << "¿Son iguales? : " << (a == b) << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * k = " << a * k << endl;
    cout << "a . b = " << a.dot(b) << endl;
    cout << "a X b = " << a.cross(b) << endl;
    cout << "|a|^2 = " << a.norm2() << endl;
    cout << "|a| = " << a.norm() << endl;
    cout << "|a-b| = " << dist(a,b) << endl;
    cout << "a.angle() = " << a.angle() << endl;
    cout << "u_a = " << a.unit() << endl;
    cout << "a_perp = " << a.perp() << endl;
    cout << "a.normal() = " << a.normal() << endl;
    cout << "a.rotate(w) = " << a.rotate(w) << endl;
    // Se rota el punto "a" respecto a "b", en sentido antihorario
    cout << "b + (a-b).rotate(w) = " << a.rotate(b,w) << endl;
    
    return 0;
}


