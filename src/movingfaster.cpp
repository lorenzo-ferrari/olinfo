#include "bits/stdc++.h"
using namespace std;
using LL = long long;

LL comunica(int n, int m, int k, int s, int e, vector<int> a, vector<int> b, vector<int> t, vector<int> r) {
	vector<vector<array<LL, 2>>> adj(n);
	for (int i = 0; i < m; ++i) {
		LL w = LL(k) * t[i] - LL(k) * (k - 1) / 2 * r[i];
		adj[a[i]].push_back({b[i], w});
		adj[b[i]].push_back({a[i], w});
	}
	vector<LL> d(n, 1e18);
	priority_queue<array<LL, 2>> Q;
	d[s] = 0;
	Q.push({0, s});
	while (!Q.empty()) {
		LL td = -Q.top()[0];
		int v =  Q.top()[1];
		Q.pop();
		if (d[v] < td) {
			continue;
		}
		for (auto [u, w] : adj[v]) {
			if (d[u] > d[v] + w) {
				d[u] = d[v] + w;
				Q.push({-d[u], u});
			}
		}
	}
	return d[e];
}
