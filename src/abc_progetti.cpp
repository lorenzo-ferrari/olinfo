// https://training.olinfo.it/task/abc_progetti
/*
 
Il problema si formula bene in termini di programmazione dinamica
  dp[0] = 1
  dp[i] = dp[i - 1] + ... + dp[i - K]
Il valore di dp[i] dipende da K (costante piccola) stati precedenti, quindi
possiamo esprimere le transizioni in termini matriciali:

Esempio: K = 4. consideriamo la seguente matrice
  M = [ [1 1 1 1];
        [1 0 0 0];
        [0 1 0 0];
        [0 0 1 0] ]
 e il vettore
   v(i) = [ dp[i];
            dp[i - 1];
            dp[i - 2];
            dp[i - 3] ]

Allora vale M * v(i) = v(i + 1) e più in generale
  M^n * v(0) = v(n).
Sappiamo calcolare M^n con l'esponenziazione veloce in O(K^3 log n) operazioni,
ampiamente entro i limiti del problema.

*/

#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;

struct Matrix {
	int n, m;
	vector<vector<LL>> a;
	Matrix(int _n, int _m = -1) : n(_n), m(_m) {
		if (m == -1)
			m = n;
		a.assign(n, vector<LL>(m));
	}

	void make_eye() {
		assert(n == m);
		a.assign(n, vector<LL>(n, 0));
		for (int i = 0; i < n; ++i)
			a[i][i] = 1;

	}

	Matrix operator*(const Matrix& other) const {
		assert(m == other.n);
		Matrix ans(n, other.m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < other.m; ++j) {
				for (int k = 0; k < m; ++k) {
					ans.a[i][j] += a[i][k] * other.a[k][j];
					ans.a[i][j] %= mod;
				}
			}
		}
		return ans;
	}
};
Matrix mat_exp(Matrix b, LL e) {
	Matrix ans(b.n);
	ans.make_eye();

	while (e > 0) {
		if (e & 1)
			ans = ans * b;
		e >>= 1;
		b = b * b;
	}

	return ans;
}

int progetti(int n, int k) {
	Matrix M(k);
	for (int i = 0; i < k; ++i)
		M.a[0][i] = 1;
	for (int i = 1; i < k; ++i)
		M.a[i][i-1] = 1;

	auto Mn = mat_exp(M, n);
	return Mn.a[0][0];
}
