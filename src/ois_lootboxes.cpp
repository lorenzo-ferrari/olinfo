#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define max(a, b) (((a) > (b) ? (a) : (b)))

const uint16_t N = 5000;
const uint16_t X = 10000;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

	uint16_t n, x;
	uint16_t p[N];
	uint16_t q[N];

	cin >> n >> x;

	for (uint16_t i = 0; i < n; i++)
		cin >> p[i] >> q[i];

	uint16_t dp[N+1][X+1] {};
	for (uint16_t i = 1; i <= n; i++) {
		for (uint16_t j = 1; j <= x; j++) {
			if (q[i-1] <= j)
				dp[i][j] = max(dp[i-1][j-q[i-1]] + p[i-1], dp[i-1][j]);
			else
				dp[i][j] = dp[i-1][j];
		}
	}

	cout << dp[n][x] << "\n";
}
