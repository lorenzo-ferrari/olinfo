#include <queue>
using namespace std;
#pragma GCC optimize ("O3")
#define F first
#define S second

int solve(int n, int m, int t, int* s, int* e) {
	vector <vector<int>> g0(n), g1(n);
	for (int i = 0; i < m; i++) {
		g0[s[i]].push_back(e[i]);
		g1[e[i]].push_back(s[i]);
	}

	const int INF = 1e9;
	vector <int> d(n, INF);
	priority_queue <pair<int, int>> Q;
	d[0] = 0;
	Q.push({0, 0});
	Q.push({-t, 0});

	while (!Q.empty()) {
		int v = Q.top().S;
		int tv=-Q.top().F;

		Q.pop();

		if (tv < t) {
			for (int i : g0[v])
				if (d[i] > tv + 1) {
					d[i] = tv + 1;
					Q.push({-d[i], i});
					Q.push({-t, i});
				}
		}
		else {
			for (int i : g1[v])
				if (d[i] > tv + 1) {
					d[i] = tv + 1;
					Q.push({-d[i], i});
				}
		}
	}

	return (d[n - 1] != INF) ? d[n - 1] : -1;
}