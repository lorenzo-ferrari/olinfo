#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int visita(int n, int m, int k, vector<int> s, vector<int> a, vector<int> b, vector<int> t) {
	vector<vector<array<int, 2>>> adj(n);
	for (int i = 0; i < m; ++i) {
		adj[a[i]].push_back({b[i], t[i]});
		adj[b[i]].push_back({a[i], t[i]});
	}

	vector<int> d(n, 0);
	priority_queue<array<int, 2>> Q;
	d[0] = k;
	Q.push({k, 0});
	while (!Q.empty()) {
		auto [td, v] = Q.top();
		Q.pop();
		if (td < d[v]) {
			continue;
		}
		for (auto [u, w] : adj[v]) {
			if (d[u] < min(d[v], w)) {
				d[u] = min(d[v], w);
				Q.push({d[u], u});
			}
		}
	}
	multiset<int> set;
	for (int i = 0; i < k; ++i) {
		set.insert(d[s[i]]);
	}
	int ans = 0;
	while (!set.empty()) {
		while (!set.empty() && *begin(set) <= ans) {
			set.erase(begin(set));
		}
		if (!set.empty()) {
			++ans;
			set.erase(begin(set));
		}
	}
	return ans;
}
