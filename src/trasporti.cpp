#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

vector <vector<pair<int, int>>> anc;
void solve(int n, int q, int br[], int a[], int b[], int s[], int e[], int sol[]) {
	vector <vector<int>> g(n + 1);
	for (int i = 0; i < n - 1; i++) {
		a[i]++, b[i]++;
		g[a[i]].push_back(b[i]);
		g[b[i]].push_back(a[i]);
	}

	// radica l'albero
	vector <int> p(n + 1, -1);
	vector <int> d(n + 1, -1);
	queue <int> Q;
	Q.push(1);
	p[1] = 0;
	d[1] = 0;
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for (int u : g[v]) {
			if (u != p[v]) {
				p[u] = v;
				d[u] = d[v] + 1;
				Q.push(u);
			}
		}
	}

	// for (int i = 1; i <= n; i++) cout << i-1 << ": " << d[i] << "\n"; return;

	const int LOG = 22;

	anc.assign(n + 1, vector <pair<int, int>> (LOG));

	for (int i = 1; i <= n; i++) {
		anc[i][0] = {i, br[i-1]};
		anc[i][1] = {p[i], br[i-1]};
		if (i != 1)
			anc[i][1].S = max(br[i-1], br[p[i]-1]);
	}

	for (int i = 2; i < LOG; i++) {
		for (int j = 1; j <= n; j++) {
			int v = anc[anc[j][i-1].F][i-1].F;
			int w = max(anc[j][i-1].S, anc[anc[j][i-1].F][i-1].S);
			anc[j][i] = {v, w};
		}
	}

	// find LCA
	for (int query = 0; query < q; query++) {
		int v = s[query] + 1, u = e[query] + 1;
		int ans = max(br[v-1], br[u-1]);
		if (d[v] > d[u])
			swap(v, u);

		while (d[u] != d[v]) {
			int tu = u;
			for (int i = 0; d[anc[u][i].F] > d[v]; i++) {
				tu = anc[u][i].F;
				ans = max(ans, anc[u][i].S);
			}
			u = p[tu];
			ans = max(ans, br[u-1]);
		}

		assert(d[u] == d[v]);

		while (v != u) {
			int tv = v, tu = u;
			for (int i = 0; anc[v][i].F != anc[u][i].F; i++) {
				tv = anc[v][i].F;
				tu = anc[u][i].F;
				ans = max(ans, anc[v][i].S);
				ans = max(ans, anc[u][i].S);
			}
			v = p[tv]; ans = max(ans, br[v-1]);
			u = p[tu]; ans = max(ans, br[u-1]);
		}

		sol[query] = ans;
	}
}