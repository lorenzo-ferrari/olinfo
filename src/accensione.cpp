#pragma GCC optimize ("O3")
void Accendi(int n, int v[], int ans[]) {
	for (int i = n; i > 0; --i) {
		for (int j = i << 1; j <= n; j += i)
			v[i] ^= ans[j];

		ans[i] = v[i] ^ 1;
	}
}