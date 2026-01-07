// 2D Fenwick Tree
//

const int N = 1000 + 5;

int n,q;
int FT[N][N];

void update(int x, int y, int d) { // Add d to (x, y)
    for (int i = x; i < N; i += i & -i) 
        for (int j = y; j < N; j += j & -j) 
            FT[i][j] += d;
}

int sum(int x, int y) { // sum (0, 0) -> (x, y)
    int sa = 0;
    for (int i = x; i; i -= i & -i) 
        for (int j = y; j; j -= j & -j)
            sa += FT[i][j];
    return sa;
}

int query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
}
