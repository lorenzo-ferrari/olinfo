#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define F first
#define S second

vector <bool> vis;
vector <vector<pair<int, int64_t>>> g;
vector <vector<pair<int, int64_t>>> t;

inline void dfs(int v) {
	vis[v] = true;
	for (auto &u : g[v]) {
		if (!vis[u.F]) {
			t[v].push_back({u});
			dfs(u.F);
		}
	}
}

//appeso -> prendi al più 1 arco figlio
vector <int64_t> dp1;
vector <int64_t> dp2;

inline int64_t f2(int v);

inline int64_t f1(int v) {
	if (dp1[v]) return dp1[v];

	int64_t ans = 0;
	int64_t mx = 0;
	for (auto &e : t[v]) {
		ans += (dp2[e.F] ? dp2[e.F] : f2(e.F));
		mx = max(mx, (dp1[e.F] ? dp1[e.F] : f1(e.F)) + e.S - (dp2[e.F] ? dp2[e.F] : f2(e.F)));
	}

	return dp1[v] = ans + mx;
}

//non appeso -> prendi al più 2 archi figli
inline int64_t f2(int v) {
	if (dp2[v]) return dp2[v];

	int64_t ans = 0;
	int64_t mx1 = 0, mx2 = 0;
	for (auto &e : t[v]) {
		ans += (dp2[e.F] ? dp2[e.F] : f2(e.F));
		int64_t val = (dp1[e.F] ? dp1[e.F] : f1(e.F)) + e.S - (dp2[e.F] ? dp2[e.F] : f2(e.F));
		if (val >= mx1) {
			mx2 = mx1;
			mx1 = val;
		}
		else if (val > mx2) {
			mx2 = val;
		}
	}

	return dp2[v] = ans + mx1 + mx2;
}

long long profitto_massimo(int n, int u[], int v[], int w[]) {
	g.resize(n);
	t.resize(n);
	dp1.resize(n);
	dp2.resize(n);
	vis.resize(n);
	for (int i = 0; i < n-1; ++i) {
		--u[i], --v[i];
		g[u[i]].push_back({v[i], w[i]});
		g[v[i]].push_back({u[i], w[i]});
	}

	dfs(0);

	return f2(0);
}