#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int gioca(int n, int k, vector<vector<int>> m) {
	int ans = 0;
	int prv = 0;
	priority_queue<array<int, 3>> Q;
	for (int i = 0; i < n; ++i) {
		Q.push({-m[i][0], i, 0});
	}
	while (!Q.empty()) {
		auto [v, i, j] = Q.top();
		Q.pop();
		if (-v > prv) {
			++ans;
			prv = -v;
		}
		if (j != k-1) {
			Q.push({-m[i][j+1], i, j+1});
		}
	}
	return ans;
}
