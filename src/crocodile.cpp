#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int64_t INF = 1e12;

vector <int64_t> d1;
vector <int64_t> d2;
vector <vector<pair<int64_t, int64_t>>> g;

int travel_plan(int n, int m, int r[][2], int l[], int k, int p[]) {
	g.resize(n);
	d1.assign(n, INF);
	d2.assign(n, INF);

	for (int i = 0; i < m; i++) {
		g[r[i][0]].push_back({r[i][1], l[i]});
		g[r[i][1]].push_back({r[i][0], l[i]});
	}

	priority_queue <pair<int64_t, int64_t>> Q;
	for (int i = 0; i < k; i++) {
		d1[p[i]] = 0;
		d2[p[i]] = 0;
		Q.push({0, p[i]});
	}

	vector <bool> vis(n);
	while (!Q.empty()) {
		int64_t v = Q.top().second;
		Q.pop();

		if (vis[v])
			continue;
		vis[v] = true;

		for (auto e : g[v]) {
			int64_t u = e.first;
			int64_t w = e.second;
			if (d1[u] > d2[v] + w) {
				d2[u] = d1[u];
				d1[u] = d2[v] + w;

				if (d2[u] != INF) {
					Q.push({-d2[u], u});
				}
			} else if (d2[u] > d2[v] + w) {
				d2[u] = d2[v] + w;

				Q.push({-d2[u], u});
			}
		}
	}

	// for (int i = 0; i < n; i++) {
	// 	cout << d1[i] << " " << d2[i] << "\n";
	// }

	return d2[0];
}
