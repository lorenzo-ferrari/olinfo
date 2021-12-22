#include <bits/stdc++.h>
using namespace std;

const int INF = 1e5 + 69;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	#ifdef EVAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;

	int dp[105][105];
	for(int i=0;i<105;i++)for(int j=0;j<105;j++)dp[i][j]=0;
	dp[1][1] = 1;

	char c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> c;
			if (c == '*')
				dp[i][j] += dp[i-1][j] + dp[i][j-1]; // dp[i-1][j-1];
			// cout << dp[i][j] << " ";
		}
		// cout << "\n";
	}

	cout << dp[n][m] << "\n";
}
