#include <bits/stdc++.h>
using namespace std;

#define x real()
#define y imag()

using pt = complex<double>;

const double eps = 1e-9;

double dot(pt a, pt b) { return real(conj(a) * b); }
double cross(pt a, pt b) { return imag(conj(a) * b); }
double norm2(pt a) { return dot(a, a); }
double dis(pt a, pt b) { return abs(a - b); } 
pt rotate(pt a) { return pt(-a.y,a.x); }
pt unite(pt v) {
	double r = abs(v);
	return pt(v.x / r, v.y/r);
}

struct Circle {
	pt C;
	double r;
	Circle() {}
	Circle(int p, int q, int R) : C(p,q), r(R) {}
	Circle(pt C, double r) : C(C), r(r) {}
	void read() {
		int p,q,R;
		cin >> p >> q >> R;
		r = R;
		C = pt(p, q);
	}
	bool is_inside(pt a) {
		return norm2(a - C) - r * r <= eps;
	}
};

//  (-)  [-e  e]   (+)
//  x < 0    x < -eps
//  x <= 0   x <= eps

vector<pt> inter(Circle c1, Circle c2) {
	if (c1.r < c2.r) swap(c1, c2);
	double d = dis(c1.C, c2.C);
	vector<pt> I;
	if (d - (c1.r + c2.r) > eps) return I;
	if (d - (c1.r - c2.r) < -eps) return I;
	double S = d, D = (c1.r * c1.r - c2.r * c2.r) / d; 
	double a = (S + D) / 2;
	double h = sqrt(c1.r * c1.r - a * a);
	pt u = unite(c2.C - c1.C);
	pt Q = c1.C + u * a;
	pt v = rotate(u);
	vector<pt> res;
	res.push_back(Q + v * h);
	res.push_back(Q - v * h);
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	cout << fixed << setprecision(10);
	int n,R; cin >> n >> R;
	vector<Circle> a(n);
	for (int i = 0; i < n; i++) {
		int p,q;
		cin >> p >> q;
		a[i] = Circle(p,q,R);
	}

	vector<pt> test;
	for (int i = 0; i < n; i++) {
		test.push_back(a[i].C);
		for (int j = i + 1; j < n; j++) {
			vector<pt> xd = inter(a[i], a[j]);
			for (pt P : xd) test.push_back(P); 
		}
	}
	int ans = 0;
	for (pt P : test) {
		int cnt = 0;
		for (int i = 0; i < n; i++) cnt += a[i].is_inside(P);
		ans = max(ans, cnt);
	}
	cout << ans << "\n";


	return 0;	
}
