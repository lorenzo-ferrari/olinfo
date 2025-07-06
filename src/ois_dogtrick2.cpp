// https://training.olinfo.it/task/ois_dogtrick2
// soluzione:
// basta capire quante acrobazie fa il cane, cioè il massimo L t.c. esiste nel
// grafo il percorso t[0] -> ... -> t[L - 1]. Occupandoci di raggiungibilità,
// ha senso passare al grafo (condensato) delle componenti fortemente connesse.
// Il problema si riduce al problema su un DAG, che si risolve processando i
// nodi in ordinamento topologico.

#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	int n; cin >> n;
	int k; cin >> k;
	vector<int> t(n);
	for (int& i : t) {
		cin >> i;
		--i;
	}
	int m; cin >> m;
	vector<set<int>> adj(k), radj(k);
	for (int i = 0, a, b; i < m; ++i) {
		cin >> a >> b;
		--a, --b;
		adj[a].insert(b);
		radj[b].insert(a);
	}

	int cnt = 0;
	vector<int> comp(k);
	{ // SCC
		vector<bool> vis(k);
		vector<int> o;
		auto dfs = [&](auto&& self, int v) -> void {
			vis[v] = true;
			for (int u : adj[v])
				if (!vis[u])
					self(self, u);
			o.push_back(v);
		};
		auto rdfs = [&](auto&& self, int v) -> void {
			vis[v] = true;
			comp[v] = cnt;
			for (int u : radj[v])
				if (!vis[u])
					self(self, u);
		};
		for (int v = 0; v < k; ++v)
			if (!vis[v])
				dfs(dfs, v);
		reverse(begin(o), end(o));
		vis.assign(k, false);
		for (int v : o) {
			if (!vis[v]) {
				rdfs(rdfs, v);
				++cnt;
			}
		}
	} // end SCC

	// condensation graph
	vector<set<int>> cadj(cnt);
	for (int a = 0; a < k; ++a)
		for (int b : adj[a])
			if (comp[a] != comp[b])
				cadj[comp[a]].insert(comp[b]);
	vector<int> o;
	{ // toposort
		vector<bool> vis(cnt);
		auto dfs = [&](auto&& self, int v) -> void {
			vis[v] = true;
			for (int u : cadj[v])
				if (!vis[u])
					self(self, u);
			o.push_back(v);
		};
		for (int v = 0; v < cnt; ++v)
			if (!vis[v])
				dfs(dfs, v);
		reverse(begin(o), end(o));
	} // end toposort

	vector<int> ct(n);
	for (int i = 0; i < n; ++i)
		ct[i] = comp[t[i]];

	vector<int> lasteq(n);
	lasteq[n - 1] = n - 1;
	for (int i = n - 2; i >= 0; --i)
		lasteq[i] = (ct[i] == ct[i + 1] ? lasteq[i + 1] : i);
	vector<int> mx(cnt);
	for (int v : o) {
		if (mx[v] == n) continue;
		if (v == ct[mx[v]])
			mx[v] = lasteq[mx[v]] + 1;
		for (int u : cadj[v])
			mx[u] = max(mx[u], mx[v]);
	}

	int len = *max_element(begin(mx), end(mx));
	int bonus = 1;
	for (int i = 0; i + 1 < len; ++i) {
		bonus += adj[t[i]].count(t[i + 1]);
	}

	cout << len + bonus << "\n";
}
