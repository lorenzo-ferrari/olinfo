#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int speedrunna(int n, int k, int a, int b) {
	vector<int> dp(k + 1, 2e9);
	dp[0] = 0;
	int t = 1, c = 1 % k; // gestisci k = 1
	for (int i = 0; i < n; ++i) {
		auto prv = dp;
		dp.assign(k + 1, 2e9);
		dp[0] = prv[k];
		for (int j = 0; j <= k; ++j) {
			int nj = min(k, j + c);
			dp[nj] = min(dp[nj], prv[j] + t);
		}
		t = t * a % 1000;
		c = c * b % k;
	}
	return *min_element(begin(dp), end(dp));
}
