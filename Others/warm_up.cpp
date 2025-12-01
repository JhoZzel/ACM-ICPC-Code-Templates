// Warm up
//

// Revisar O(n^3) con factor de 1/6. Buscar el max n tal que de TLE
int main() {
    int res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            for(int k = j; k < n; k++) {
                res += (i + j + k) & 1;
            }
        }
    }
    cout << res << endl;
    return 0;
}

// Revisar la profundidad de la pila de recursion. Probar con diferentes n hasta TLE

const int n = 1e6;
int sz[n + 1];
vector<int> G[n + 1];

void DFS(int u, int p = -1) {
    sz[u] = 1;
    for(int v : G[u]) {
        if(v == p) continue;
        DFS(v, u);
        sz[u] += sz[v];
    }
}

int main() {
    for(int i = 1; i < n; i++) {
        G[i - 1].emplace_back(i);
        G[i].emplace_back(i - 1);
    }
    DFS(0);
    cout << sz[0] << endl;
    return 0;
}

// Probar n productos modulares. Probar n hasta TLE

const int n = 100000000;
const int MOD = 1e9 + 7;

int main() {
    int res = 1;
    for(int i = 1; i <= n; i++) {
        res = (1ll * res * i) % MOD;
    }
    cout << res << endl;
    return 0;
}

// Probar O(N sqrt(N))
const int n = 1000000;

int main() {
    int s = sqrt(2 * n);
    int res = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= s; j++) {
            res ^= i + j;
        }
    }
    cout << res << endl;
    return 0;
}

// Declarar un vector de tamano n (notemos q puede ser hasta 2 *n, la memoria usada)
// Probar hasta llegar un MLE o RTE

const int n = 3e8;

int main() {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    cout << accumulate(a.begin(), a.end(), 0LL) << endl;
    return 0;
}


// Acceso a indices negativos. Probar si da WA o RTE
const int n = 10;

int main() {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    int at = 0;
    int res = 0;
    while(at >= -5) {
        res += a[at--];
    }
    cout << res << endl;
    return 0;
}

// Acceso a memoria no declarada. Probar y ver si da RTE o WA.

const int n = 10;

int main() {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    int at = n - 1;
    int res = 0;
    while(at < 2 * n) {
        res += a[at++];
    }
    cout << res << endl;
    return 0;
}
