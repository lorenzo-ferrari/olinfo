// https://training.olinfo.it/#/task/weoi_trees/statement
// dp[v][0]: ways of choosing a valid non-empty subset of subtree(v) assuming
// 			 none of v's ancestors are chosen
// dp[v][1]: ways of choosing a valid non-empty subset of subtree(v) assuming
// 			 one of v's ancestors is already chosen
// answer = dp[0][0]
// after appropriate semplifications, the transictions appear as in the code below
#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;

int count_sets(int n, vector<int> a, vector<int> b) {
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; ++i) {
		adj[a[i]].push_back(b[i]);
		adj[b[i]].push_back(a[i]);
	}
	vector<array<LL, 2>> dp(n);
	auto dfs = [&](auto&& self, int v, int p) -> void {
		for (int u : adj[v]) {
			if (u == p) continue;
			self(self, u, v);
		}
		LL prd = 1;
		for (int u : adj[v]) {
			if (u == p) continue;
			prd = prd * (dp[u][1] + 1) % mod;
			dp[v][0] += dp[u][0];
		}
		dp[v][0] = (dp[v][0] + prd) % mod;
		dp[v][1] = (dp[v][1] + prd) % mod;
	};
	dfs(dfs, 0, -1);
	return dp[0][0];
}
