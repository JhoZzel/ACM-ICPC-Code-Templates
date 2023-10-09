#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false); cin.tie (NULL)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) x.size()
#define PI acos(-1)
#define F first
#define S second
using namespace std;
typedef long long ll;

#include "ClosestPair.h"

int main() {
    P C,a,b;
    double k = 2.5, w = PI/4, r;
    /*
    cout << "========= BASIC THING ==========\n";
    cout << "Punto A : "; cin >> a;
    cout << "Punto B : "; cin >> b;
    
    cout << "Punto MIN : " << min(a,b) << endl; 
    cout << "Punto MAX : " << max(a,b) << endl;
    cout << "¿Son iguales? : " << (a == b) << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a * k = " << a * k << endl;
    cout << "a . b = " << a.dot(b) << endl;
    cout << "a X b = " << a.cross(b) << endl;
    cout << "|a|^2 = " << a.dist2() << endl;
    cout << "|a| = " << a.norm() << endl;
    cout << "|a-b| = " << dist(a,b) << endl;
    cout << "a.angle() = " << a.angle() << endl;
    cout << "u_a = " << a.unit() << endl;
    cout << "a_perp = " << a.perp() << endl;
    cout << "a.normal() = " << a.normal() << endl;
    cout << "a.rotate(w) = " << a.rotate(w) << endl;
    // Se rota el punto "a" respecto a "b", en sentido antihorario
    cout << "b + (a-b).rotate(w) = " << a.rotate(b,w) << endl;
    */
    
    /*
    cout << "========== Circle Intersection ===========" << endl;
    cout << "Centro : "; cin >> C;
    cout << "Radio: "; cin >> r;
    cout << "Recta: "; cin >> a >> b;
    vector<P> cl = circleLine(C, r, a, b);
    for (P p : cl) cout << p << "\n";
    */
    
    /*
    cout << "========== Circle Tangents ===========" << endl;
    P C1,C2;
    double r1,r2;
    cout << "Centro 1: "; cin >> C1;
    cout << "radio 1: "; cin >> r1;
    cout << "Centro 2: "; cin >> C2;
    cout << "radio 2: "; cin >> r2;
    vector<pair<P,P>> ans = tangents(C1,r1,C2,r2);
    for (auto p : ans) cout << p.F << " " << p.S << endl;
    */
    
    /*
    cout << "============ Closest Pair ============" << endl;
    int n;
    cout << "n = "; cin >> n;
    vector<Point<ll>> points(n);
    for (int i=0; i<n; i++) cin >> points[i];
    pair<P,P> ans = closest(points);
    cout << ans.F << " " << ans.S << endl; 
    */
    return 0;
}


