/*

1 <= a, b, c, d <= 5000

(x, y, z)
0 <= x, y, z

0 <= x <= d/a
0 <= y <= d/b 
0 <= z <= d/c

int ans = 0;
for (int x=0; a * x <= d; ++x)
    for (int y=0; a * x + b * y <= d; ++y) {
        if ((d - (a * x + b * y)) % c == 0) {  
            ans += 1;
        }
    }


// 0 <= c <= 1e18
// x >= 0

// 0 <= d(x) <= 162

//x = (d(x) + sqrt(d(x)^2 + 4c)) / 2 ~ 2 * d(x) + 2 sqrt(c)

// x < e^x

f(x) = -x^2 + d(x) * x + c 

d(x) := suma de digitos de x.

vector<ll> res;
for (int i = 0; i <= 162; ++i) {
    //f(x) = -x^2 + i * x + c

    ll temp = i*i + 4 * c;
    ll sqrt_temp = sqrt(temp);

    if (sqrt_temp * sqrt_temp == temp) {
        ll x1 = i + sqrt_temp;
        ll x2 = i - sqrt_temp;

        if (x1 % 2 == 0 && x1 >= 0 && d(x1) == i) res.push_back(x1 / 2);
        if (x2 % 2 == 0 && x2 >= 0 && d(x2) == i) res.push_back(x2 / 2);
    }

    //x = (i +/- sqrt(i^2 + 4c))/2
}


N: (x1, y1), (x2, y2), ..., (xn, yn)


// O(n^4) -> hallar distancias -> ordenar -> {l, l, l, l, 2l, 2l}

// O(n^3 log n) -> hallar la distancia entre 3 -> ordenar -> {l, l, 2l} -> reflejar

// 
// O(n^2) -> hallar diagonales como vector (p[i] - p[j]) -> halar el centro (p[i] + p[j])
// vector<pair<Point, Point>> vectores,

// O(n^2 logn)

for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
        Point centrox2 = p[i] + p[j];
        Point diagonal = rectifico(p[i] - p[j]);
        bool cuadrante_1 = 1;
        if (esta_en_cuadrante_2(diagonal)) {
            cuadrante_1 = 0;
            diagonal = diagonal.perp();
        }
        conjunto.push_back({centrox2, diagonal, cuadrante_1});
    }
}

sort(conjunto.begin(), conjunto.end());
int ans = 0;
for (int i = 1; i < conjunto.size(); ++i) {
    if (conjunto[i].X == conjunto[i-1].X && conjunto[i].Y == conjunto[i-1].Y) {
        if (conjunto[i].Z != conjunto[i-1].Z) {
            ans += 1;
        }
    }
}

*/