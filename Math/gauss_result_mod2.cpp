/**
 * ============================================================================
 * ELIMINACIÓN DE GAUSS-JORDAN EN GF(2) (Módulo 2 / XOR)
 * ============================================================================
 * 
 * RESTRICCIONES Y DETALLES TÉCNICOS: 
 * - Diseñada para matrices CUADRADAS (N x N) con elementos booleanos (0 o 1).
 * - Utiliza `bitset` para paralelizar operaciones a nivel de bits. Esto requiere
 *   definir un límite máximo `MAXN` en tiempo de compilación.
 * 
 * INTERPRETACIÓN DE LOS RESULTADOS (GaussResultGF2):
 * 
 * 1. Rango (rnk):
 *    - Si `rnk == n`: La matriz es de RANGO COMPLETO.
 *      -> Es INVERTIBLE.
 *      -> Las filas/columnas son linealmente independientes.
 *    - Si `rnk < n`: La matriz es SINGULAR.
 *      -> Existen redundancias lógicas (ej. un estado se puede alcanzar 
 *         combinando XORs de otros estados).
 * 
 * 2. Determinante (det):
 *    - En GF(2) el determinante solo puede ser 1 (invertible) o 0 (singular).
 *    - NO HAY CAMBIOS de signo al intercambiar filas, ya que 1 == -1 (mod 2).
 * 
 * 3. Inversa (inv):
 *    - Contiene la matriz inversa A^-1 tal que (A * A^-1) ^ Matriz Identidad = 0.
 *    - Válida únicamente si `rnk == n`.
 * 
 * COMPLEJIDAD (Usando Bitsets):
 * - Tiempo: O(N^3 / 64) -> Extremadamente rápido para N hasta 2^12 ~ 1063ms.
 * - Memoria: O(N^2 / 64)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1 << 12; 

struct GaussResult {
	int rnk;
	int det; 
	vector<bitset<MAXN>> inv;
};

GaussResult gauss_jordan(int n, vector<bitset<MAXN>>& A) {
	// Augmented matrix
	vector<bitset<2 * MAXN>> aug(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (A[i][j]) aug[i].set(j);
		}
		aug[i].set(n + i); // Id
	}

	int rnk = 0;
	int det = 1;
	for (int c = 0; c < n; c++) { // iteramos sobre cada columna
		int p = rnk;
		while (p < n and !aug[p][c]) p++; // buscamos un pivote == 1

		if (p == n) {
			det = 0;
			continue;
		}

		if (p != rnk) {
			swap(aug[rnk], aug[p]);
		}

		// Aniquilamos los 1s en la columna 'c' de las demás filas
		for (int i = 0; i < n; i++) {
			if (i != rnk and aug[i][c]) {
				aug[i] ^= aug[rnk]; // XOR en toda la fila en un solo golpe de reloj
			}
		}
		rnk++;
	}

	vector<bitset<MAXN>> inv(n);
	if (rnk == n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (aug[i][n + j]) inv[i].set(j);
			}
		}
	}

	return {rnk, det, inv};
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	
	int n; cin >> n;
	vector<bitset<MAXN>> a(n);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < n; j++) {
			if (s[j] == '1') a[i].set(j);
		}
	}
	
	GaussResult gs = gauss_jordan(n, a);
	
	if (gs.rnk != n) cout << "-1\n";
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << gs.inv[i][j];
			}
			cout << "\n";
		}
	}

	return 0;
}

// https://judge.yosupo.jp/submission/405869
