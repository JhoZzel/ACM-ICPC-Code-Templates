
double f(double x) {
    return cos(x) / (1 + x * x);
} 

double simpson(double a, double b) {
    const int n = 2 * 100; // Number of steps (multiplied by two)
    double h = (b - a) / n;
    double ans = f(a) + f(b); // a = x_0  b = x_2n
    for (int i = 1; i <= n - 1; i++) { // Refer to final Simpson's formula
        double x = a + i * h;
        ans += (i & 1 ? 4  : 2) * f(x);
    }
    ans *= h / 3;
    return ans;
}

