// https://training.olinfo.it/task/ois_exhibition3
#include "bits/stdc++.h"
using namespace std;
using LL = long long;

vector<bool> visit(vector<int> src, const vector<vector<int>> adj, vector<int> threshold) {
	int n = adj.size();
	vector<bool> vis(n);
	vector<int> cnt(n);

	queue<int> Q;
	for (int x : src) {
		Q.push(x);
		vis[x] = true;
	}
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();

		for (int u : adj[v]) {
			if (!vis[u] && ++cnt[u] == threshold[u]) {
				vis[u] = true;
				Q.push(u);
			}
		}
	}

	return vis;
}

int main() {
	int n; cin >> n;
	int m; cin >> m;

	string c; cin >> c;
	vector<vector<int>> adj(n), rdj(n);

	for (int i = 0, a, b; i < m; ++i) {
		cin >> a >> b;
		adj[a].push_back(b);
		rdj[b].push_back(a);
	}

	// identify sinks
	vector<int> threshold(n);
	for (int i = 0; i < n; ++i)
		threshold[i] = (c[i] == 'C' ? 1 : adj[i].size());
	vector<int> src;
	for (int i = 0; i < n; ++i)
		if (adj[i].empty())
			src.push_back(i);
	auto sink = visit(src, rdj, threshold);

	// identify cat cycles
	src.clear();
	threshold.assign(n, 0);
	vector<vector<int>> catrdj(n);
	for (int i = 0; i < n; ++i) {
		if (c[i] != 'C') continue;
		for (int j : adj[i]) {
			if (c[j] != 'C') continue;
			catrdj[j].push_back(i);
			++threshold[i];
		}
	}
	for (int i = 0; i < n; ++i)
		if (c[i] == 'C' && threshold[i] == 0)
			src.push_back(i);
	auto catsink = visit(src, catrdj, threshold);

	// identify nodes from which the cat player can reach cat cycles
	src.clear();
	threshold.assign(n, 0);
	for (int i = 0; i < n; ++i)
		if (c[i] == 'C' && !catsink[i])
			src.push_back(i);
	for (int i = 0; i < n; ++i)
		threshold[i] = (c[i] == 'C' ? 1 : adj[i].size());
	auto catcycle = visit(src, rdj, threshold);

	for (int i = 0; i < n; ++i)
		cout << (!sink[i] && !catcycle[i]);
	cout << "\n";
}
