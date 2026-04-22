// Double comparator

constexpr double EPS = 1e-9, PI = acos(-1.0);

using T = double;

int sgn(T x) {
  if (x < -EPS) return -1;
  if (x > EPS) return 1;
  return 0;
}

bool le(T a, T b) { return sgn(a - b) < 0; }
bool leq(T a, T b) { return sgn(a - b) <= 0; }
bool gr(T a, T b) { return sgn(a - b) > 0; }
bool greq(T a, T b) { return sgn(a - b) >= 0; }
bool eq(T a, T b) { return sgn(a - b) == 0; }

