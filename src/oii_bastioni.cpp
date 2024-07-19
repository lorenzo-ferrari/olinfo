#include "bits/stdc++.h"
#pragma GCC optimize("O3")
using namespace std;

int arrampicate(int N, string S) {
	auto solve = [&](const string& s) -> int {
		int n = s.size();
		vector<array<array<int, 2>, 2>> dp(n+1);
		// 0: <
		// 1: >
		dp[0][0][0] = dp[0][1][0] = 1;
		dp[0][0][1] = dp[0][1][1] = 1;
		for (int i = 0; i < n; ++i) {
			if (s[i] == '=') {
				dp[i + 1][0][0] = dp[i][0][0];
				dp[i + 1][1][0] = dp[i][1][0];
				dp[i + 1][0][1] = dp[i][0][1];
				dp[i + 1][1][1] = dp[i][1][1];
			} else if (s[i] == '<') {
				dp[i + 1][0][0] = dp[i][0][0];
				dp[i + 1][1][0] = min(dp[i][0][0], dp[i][1][0]) + 1;
				dp[i + 1][0][1] = dp[i][0][1];
				dp[i + 1][1][1] = min(dp[i][0][1], dp[i][1][1]) + 1;
			} else if (s[i] == '>') {
				dp[i + 1][0][0] = min(dp[i][0][0], dp[i][1][0]) + 1;
				dp[i + 1][1][0] = dp[i][1][0];
				dp[i + 1][0][1] = min(dp[i][0][1], dp[i][1][1]) + 1;
				dp[i + 1][1][1] = dp[i][1][1];
			} else if (s[i] == '?') {
				// collapse the previous scenarios
				// s[i] to '<'
				dp[i + 1][0][0] = max(dp[i][0][0], dp[i][0][1]);
				dp[i + 1][1][0] = max(min(dp[i][0][0], dp[i][1][0]), min(dp[i][0][1], dp[i][1][1])) + 1;
				// s[i] to '>'
				dp[i + 1][0][1] = max(min(dp[i][0][0], dp[i][1][0]), min(dp[i][0][1], dp[i][1][1])) + 1;
				dp[i + 1][1][1] = max(dp[i][1][0], dp[i][1][1]);
			}
		}

		return max(min(dp[n][0][0], dp[n][1][0]), min(dp[n][0][1], dp[n][1][1]));
	};

	int ans = 0;
	string T{};
	S.push_back('#');
	for (int i = 0; i < (int)S.size(); ++i) {
		if (S[i] == '#') {
			ans += solve(T);
			T = "";
		} else {
			T.push_back(S[i]);
		}
	}

	return ans;
}
