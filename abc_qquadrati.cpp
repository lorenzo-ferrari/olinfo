#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int N = 1 << 15;
int dp[5][N + 1];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	#ifdef EVAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif


	for (int i = 0; i < 5; i++) dp[i][0] = 1;

	for (int i = 1; i*i <= N; i++) {
		for (int j = i*i; j <= N; j++) {
			dp[1][j] += dp[0][j-i*i];
			dp[2][j] += dp[1][j-i*i];
			dp[3][j] += dp[2][j-i*i];
			dp[4][j] += dp[3][j-i*i];
		}
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		cout << dp[4][n] << " ";
	}
}
