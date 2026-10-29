// Random Numbers
using ll = long long;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

ll random(ll L, ll R) {
    return uniform_int_distribution<ll>(L, R)(rnd);
}

// Max y min 

int max_int = numeric_limits<int>::max();
int min_int = numeric_limits<int>::min();

long long max_ll = numeric_limits<long long>::max();
long long min_ll = numeric_limits<long long>::min();

// Enteros sin signo (el mínimo siempre es 0)
unsigned int max_uint = numeric_limits<unsigned int>::max();
unsigned long long max_ull = numeric_limits<unsigned long long>::max();

// Flotantes
double max_double = numeric_limits<double>::max();
double min_positivo_double = numeric_limits<double>::min(); // El valor > 0 más pequeño
double min_real_double = numeric_limits<double>::lowest();  // El valor más negativo



import sys
sys.set_int_max_str_digits(0) // quitar el limite de digitos
sys.setrecursionlimit(200000) // limite de recursion
		
// Fast IO
input = sys.stdin.readline
input = io.BytesIO(os.read(0,os.fstat(0).st_size)).readline

// Exponenciación modular: (a^b) % MOD
res = pow(a, b, MOD)

// Inverso modular: (a^-1) % MOD
// IMPORTANTE: Solo funciona en Python 3.8+ usando el -1. 
// a y MOD deben ser coprimos (math.gcd(a, MOD) == 1)
inv = pow(a, -1, MOD)

// Truco para Conversión de Bases con Big Ints
numero_binario = "1101010101010101010101010"
decimal = int(numero_binario, 2)

numero_hex = "F3A2B1C9"
decimal_hex = int(numero_hex, 16)
