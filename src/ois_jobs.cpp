#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	LL n; cin >> n;
	LL m; cin >> m;
	vector<LL> t(n), p(n);
	for (int i = 0; i < n; ++i) cin >> t[i];
	for (int i = 0; i < n; ++i) cin >> p[i];

	// idea: repeat a single task for at least M - GUESS days
	static constexpr int GUESS = 1 << 18;
	vector<LL> dp(GUESS + 1);
	for (int i = 0; i < n; ++i) {
		for (int j = t[i]; j <= GUESS; ++j) {
			dp[j] = max(dp[j], p[i] + dp[j - t[i]]);
		}
	}
	if (m <= GUESS) {
		cout << dp[m] << "\n";
	} else {
		LL ans = 0;
		for (int i = 0; i < n; ++i) {
			LL cnt = (m - GUESS + t[i] - 1) / t[i];
			ans = max(ans, dp[m - cnt * t[i]] + cnt * p[i]);
		}
		cout << ans << "\n";
	}
}
