#include <bitset>
#include <iostream>
#pragma GCC optimize ("O3")

#define int long long

const int m = 10000019;

int dp[2][m];
int b[2][m], i[2];
int inv[m];

int32_t main() {
	inv[1] = 1;
	for (int k = 2; k < m; k++)
		inv[k] = m - (m/k) * inv[m%k] % m;

	int n, t;
	scanf("%d%d", &n, &t);

	dp[1][1] = 1;
	for (int it = 0; 2 * it < n; ++it) {
		int w = it & 1;

		for (int i = 1; i < m; ++i) {
			if (!dp[w ^ 1][i]) continue;
			for (int c = 1; c < 10; ++c) {
				int x = i * c % m;
				dp[w][x] += dp[w ^ 1][i];
				if (dp[w][x] > m)
					dp[w][x] -= m;
			}
			if (2 * it + 1 != n)
				dp[w ^ 1][i] = 0;
		}
	}

	int ans = 0;
	int a = 1 - (((n+1)>>1)&1);
	int b = 1 - ((n-((n+1)>>1))&1);
	for (int k = 1; k < m; k++)
		ans = (ans + dp[a][k] * dp[b][t * inv[k] % m]) % m;

	printf("%d\n", ans);
}
