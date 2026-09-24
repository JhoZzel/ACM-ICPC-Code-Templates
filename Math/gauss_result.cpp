#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;
using vl = vector<ll>;
using vvl= vector<vl>;

const int MOD = 998244353; // primo

/**
 * ============================================================================
 * ELIMINACIÓN DE GAUSS-JORDAN (Módulo 998244353)
 * ============================================================================
 * 
 * RESTRICCIÓN IMPORTANTE: 
 * Esta plantilla está diseñada específicamente para matrices CUADRADAS (N x N).
 * 
 * INTERPRETACIÓN DE LOS RESULTADOS (GaussResult):
 * 
 * 1. Rango (rnk):
 *    - Si `rnk == n`: La matriz es de RANGO COMPLETO. 
 *      -> Es INVERTIBLE.
 *      -> Su determinante es distinto de cero (det != 0).
 *      -> Un sistema de ecuaciones Ax = b tendría una SOLUCIÓN ÚNICA.
 *    - Si `rnk < n`: La matriz es SINGULAR.
 *      -> NO es invertible (la matriz `inv` estará llena de ceros o no será válida).
 *      -> Su determinante es cero (det == 0).
 *      -> Un sistema Ax = b tendría infinitas soluciones o ninguna (dependiendo de b).
 *    - Si `rnk == n - 1` (Caso especial común): 
 *      -> La dimensión del espacio nulo (kernel) es exactamente 1. 
 *      -> Significa que hay exactamente 1 variable libre si estuviéramos resolviendo Ax = 0.
 * 
 * 2. Determinante (det):
 *    - Calculado módulo 998244353. Si el determinante es 0, la matriz no tiene inversa.
 * 
 * 3. Inversa (inv):
 *    - Solo tiene sentido y es correcta si `rnk == n`.
 *    - Contiene la matriz inversa A^-1 tal que (A * A^-1) % MOD = Matriz Identidad.
 * 
 * GUÍA DE USO:
 * 1. Declara tu matriz N x N: `vvl a(n, vl(n));`
 * 2. Llénala con tus valores.
 * 3. Llama a la función: `GaussResult gs = gauss_jordan(a);`
 * 4. Valida si es invertible comprobando el rango: `if (gs.rnk == n) { ... }`
 * 
 * COMPLEJIDAD:
 * - Tiempo: O(N^3)
 * - Memoria: O(N^2)
 * ============================================================================
 */

struct GaussResult {
	int rnk;
	ll det;
	vvl inv;
};

ll bpow(ll a, ll e) {
	ll r = 1;
	while(e) {
		if (e & 1) r = r * a % MOD;
		a = a * a % MOD;
		e >>= 1;
	}
	return r;
}

GaussResult gauss_jordan(vector<vector<ll>>& A) { // A % MOD
	int n = A.size();
	vvl aug(n, vl(2 * n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			aug[i][j] = A[i][j];
		}
		aug[i][n + i] = 1; // id
	}

	int rnk = 0;
	ll det = 1;
	for (int c = 0; c < n; c++) { // col
		int p = rnk;
		while (p < n and aug[p][c] == 0) p++;

		if (p == n) {
			det = 0;
			continue; // calculate rank
		}

		if (p != rnk) {
			swap(aug[rnk], aug[p]);
			det = (MOD - det) % MOD; 
		}

		ll val_p = aug[rnk][c];
		det = (det * val_p) % MOD;
		ll inv_p = bpow(val_p, MOD - 2);

		for (int j = c; j < 2 * n; j++) {
			aug[rnk][j] = aug[rnk][j] * inv_p % MOD;
		}

		for (int i = 0; i < n; i++) {
			if (i != rnk and aug[i][c] != 0) {
				ll f = aug[i][c];
				for (int j = c; j < 2 * n; j++) {
					aug[i][j] -= f * aug[rnk][j] % MOD;
					aug[i][j] %= MOD;
					if (aug[i][j] < 0) aug[i][j] += MOD;
				}
			}
		}
		rnk++;
	}

	vvl inv(n, vl(n));
	if (rnk == n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				inv[i][j] = aug[i][n + j];
			}
		}
	}

	return {rnk, det, inv};
}


int main() {
	cin.tie(0) -> sync_with_stdio(0);
	
	int n; cin >> n;
	vvl a(n, vl(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	GaussResult gs = gauss_jordan(a);
	if (gs.rnk != n) cout << "-1\n";
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << gs.inv[i][j] << " ";
			}
			cout << "\n";
		}
	}


	return 0;
}
