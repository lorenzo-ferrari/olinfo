#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define F first
#define S second

const int INF = 1e9;
void risolvi(int n, int m, int a[], int b[], int h[], long long ans[]) {
	vector <vector<pair<int, int>>> g(n+1);
	for (int i = 0; i < n; ++i) {
		g[a[i]].push_back({b[i], h[i]});
		g[b[i]].push_back({a[i], h[i]});
	}

	vector <int> d(n+1, INF);
	vector <bool> vis(n+1);

	priority_queue <pair<int, int>> Q;

	Q.push({0, 1});
	d[1] = 0;

	int r = 0;
	while (!Q.empty()) {
		int th = Q.top().F;
		vector <int> buff;

		while (!Q.empty() && Q.top().F == th) {
			int v = Q.top().S;
			Q.pop();

			if (vis[v])
				continue;
			vis[v] = true;

			buff.push_back(v);
		}

		th = -th;
		for (int v : buff) {
			ans[v] = (long long)th * r;
			for (auto e : g[v]) {
				if (d[e.F] > e.S) {
					d[e.F] = e.S;
					Q.push({-e.S, e.F});
				}
			}
		}

		r += buff.size();
	}
}
