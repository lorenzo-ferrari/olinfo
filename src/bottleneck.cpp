#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int INF = 1e9;
int Analizza(int n, int m, int W, int L, int a[], int b[], int w[], int R, int C) {
	vector <vector<pair<int, int>>> g(n);
	for (int i = 0; i < m; i++) {
		--a[i], --b[i];
		g[a[i]].push_back({b[i], w[i]});
		g[b[i]].push_back({a[i], w[i]});
	}

	vector <int> d(n, INF);
	vector <int> ans(n, INF);
	vector <bool> vis(n);

	priority_queue <array<int, 3>> Q;
	Q.push({0, INF, L-1});

	while (!Q.empty()) {
		int v = Q.top()[2];
		Q.pop();

		if (vis[v])
			continue;
		vis[v] = true;

		for (auto e : g[v]) {
			int u = e.first;
			int p = e.second;
			if (d[u] == INF) {
				d[u] = d[v] + 1;
				ans[u] = min(ans[v], p);
				Q.push({-d[u], -ans[u], u});
			} else if (d[u] == d[v] + 1 && ans[u] > min(ans[v], p)) {
				ans[u] = min(ans[v], p);
				Q.push({-d[u], -ans[u], u});
			}
		}
	}

	return ans[W-1];
}
