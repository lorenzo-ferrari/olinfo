#include<bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC otpimize ("Ofast")
using namespace std;

int speedrunna(int n, int k, int a, int b) {
	int dp[51];
	int prv[51];

	for (int i = 1; i <= k; i++)
		dp[i] = 1e9;

	for (int i = 0, t = 1, c = 1 % k; i < n; i++, t = t * a % 1000, c = c * b % k) {
		for (int j = 0; j <= k; j++) {
			prv[j] = dp[j];
			dp[j] = 1e9;
		}

		for (int j = 0; j <= k; j++) {
			if (j >= c) dp[j] = min(dp[j], prv[j - c] + t);
			if (j + c >= k) dp[k] = min(dp[k], prv[j] + t);
		}

		dp[0] = min(dp[0], prv[k]);

	}

	int ans = 1e9;
	for (int i = 0; i <= k; i++)
		ans = min(ans, dp[i]);

	return ans;
}

#ifndef EVAL
int main() {
	int n, k, a, b;
	cin >> n >> k >> a >> b;
	cout << speedrunna(n, k, a, b) << "\n";
}
#endif
