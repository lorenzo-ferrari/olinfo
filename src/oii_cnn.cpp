// https://training.olinfo.it/task/oii_cnn
#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr int INF = 1e9;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n; cin >> n;
	int m; cin >> m;

	vector<array<int, 2>> coord(n + 1);
	coord[0] = {1, 1};
	for (int i = 1; i <= n; ++i) {
		cin >> coord[i][0] >> coord[i][1];
	}

	// {che troupe riprende l'i-esimo evento, i, dove sta l'altro bro}
	array<vector<vector<int>>, 2> dp;
	dp[0].assign(n + 1, vector<int>(m + 1, INF));
	dp[1].assign(n + 1, vector<int>(m + 1, INF));
	dp[0][0][1] = dp[1][0][1] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int t = 0; t < 2; ++t) {
			for (int oth = 1; oth <= m; ++oth) {
				dp[t][i][oth] = dp[t][i - 1][oth] + abs(coord[i][t] - coord[i - 1][t]);
				if (oth == coord[i - 1][t ^ 1]) {
					for (int prv = 1; prv <= m; ++prv) {
						dp[t][i][oth] = min(dp[t][i][oth], dp[t ^ 1][i - 1][prv] + abs(coord[i][t] - prv));
					}
				}
			}
		}
	}
	vector<array<int, 2>> stati(1, {0, 1}); // {t_i, oth_i} ottimali in ordine inverso
	for (int t = 0; t < 2; ++t) {
		for (int oth = 1; oth <= m; ++oth) {
			auto& state = stati.back();
			if (dp[t][n][oth] < dp[state[0]][n][state[1]]) {
				state = {t, oth};
			}
		}
	}
	for (int i = n; i > 1; --i) {
		auto [t, oth] = stati.back();
		if (dp[t][i - 1][oth] + abs(coord[i][t] - coord[i - 1][t]) == dp[t][i][oth]) {
			stati.push_back({t, oth});
			continue;
		}
		if (oth == coord[i - 1][t ^ 1]) {
			for (int prv = 1; prv <= m; ++prv) {
				if (dp[t ^ 1][i - 1][prv] + abs(coord[i][t] - prv) == dp[t][i][oth]) {
					stati.push_back({t ^ 1, prv});
					break;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << "RC"[stati[n - i][0]] << "\n";
	}
}
