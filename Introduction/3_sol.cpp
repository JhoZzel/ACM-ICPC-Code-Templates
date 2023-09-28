#include<bits/stdc++.h>
using namespace std;
 
struct Point {
    using P = Point;
    double x, y;
    explicit Point(double x=0, double y=0) : x(x), y(y) {}
    P operator+(P other) {return P(x+other.x, y+other.y);}
    P operator-(P other) {return P(x-other.x, y-other.y);}
    P operator*(double c) {return P(x*c, y*c);}
    P operator/(double c) {return P(x/c, y/c);}
    P perp() {return P(-y, x);}
 
    friend istream& operator>>(istream& is, P& other) {
        return is >> other.x >> other.y;}
    friend ostream& operator<<(ostream& os, P other) {
        return os << other.x << " " << other.y;}
};
 
double ccw(Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}
 
int main() {
    vector<Point> P(3);
    for (auto& p : P) cin>>p;
    Point X = (P[0] + P[1]) / 2;
    Point Y = (P[1] + P[2]) / 2;
    Point vX = (P[1] - P[0]).perp();
    Point vY = (P[2] - P[1]).perp();
    Point C = X + vX * ccw(Y - X, vY) / ccw(vX, vY);
    cout << C << endl;
    return 0;
}