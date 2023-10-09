/**
 * Author: Ulf Lundstrom, Miguel Miní
 * Date: 2020-07-10
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */

#pragma once

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>

struct Point {
    typedef Point P;
    double x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P other) const { return P(x + other.x, y + other.y); }
    P operator-(P other) const { return P(x - other.x, y - other.y); }
    P operator*(T c) const { return P(x * c, y * c); }
    P operator/(T c) const { return P(x/c, y/c); }
    //friend T operator*(T c, const P p) { return p * c; }
    T operator*(P other) const { return x * other.x + y * other.y; }
    T operator^(P other) const { return x * other.y - y * other.x; }
    T dot(P other) const { return (*this) * other; }
    T cross(P other) const { return (*this) ^ other; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double norm() const { return sqrt((double)dist2()); }
    friend double dist(P p, P q) { return (p - q).norm(); }
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/norm(); }
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    P rotate(Point other, double a) const {
        return (*this - other).rotate(a) + other;
    }
    friend istream& operator>>(istream& is, P& other) {
        return is >> other.x >> other.y;
    }
    friend ostream& operator<<(ostream& os, P other) {
        return os << "(" << other.x << "," << other.y << ")";
    }
};
