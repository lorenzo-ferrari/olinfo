#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> dp(n, vector<int> (m+1));
	for (int i = 1; i <= m; i++)
		dp[n-1][i] = 1;
	for (int i = n-2; i >= 0; i--) {
		int sum = 0;
		for (int j = m; j > 0; j--) {
			for (int k = 2*j; k <= m && k < 2*(j+1); k++)
				sum = (sum + dp[i+1][k]) % mod;
			dp[i][j] = sum;
		}
	}

	int ans = 0;
	for (int i = 1; i <= m; i++)
		ans = (ans + dp[0][i]) % mod;
	cout << ans << "\n";
}
