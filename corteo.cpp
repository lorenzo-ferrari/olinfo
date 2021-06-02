#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define F first
#define S second

const int INF = 1e9;

int N, P1, D1, P2, D2;
int d[1001][1001];
vector <vector<int>> g;

void bfs(int v) {
	vector <int> vis(N);
	queue <int> Q;
	Q.push(v);
	vis[v] = true;
	while (!Q.empty()) {
		int x = Q.front();
		Q.pop();
		for (int u : g[x]) {
			if (!vis[u]) {
				vis[u] = true;
				d[v][u] = d[v][x] + 1;
				Q.push(u);
			}
		}
	}
}

bool prova(int val) {
    if (d[P1][P2] < val) return false;
	vector <vector<bool>> vis(N, vector <bool> (N));
	queue <pair<int, int>> Q;
	Q.push({P1, P2});

	while (!Q.empty()) {
		int v = Q.front().F;
		int u = Q.front().S;
		Q.pop();

		if (v == D1 && u == D2 && d[v][u] >= val)
			return true;

		for (int x : g[v]) {
			if (d[x][u] >= val && !vis[x][u]) {
				vis[x][u] = true;
				Q.push({x, u});
			}
		}

		for (int y : g[u]) {
			if (d[v][y] >= val && !vis[v][y]) {
				vis[v][y] = true;
				Q.push({v, y});
			}
		}
	}

	return false;
}

int pianifica(int n, int m, int p1, int d1, int p2, int d2, int a[], int b[]) {
	N = n, P1 = p1, D1 = d1, P2 = p2, D2 = d2;
	g.resize(n);
	for (int i = 0; i < m; i++) {
		g[a[i]].push_back(b[i]);
		g[b[i]].push_back(a[i]);
	}

	for (int i = 0; i < n; i++) bfs(i);
	
	if (p1 == d1 && p2 == d2) return d[p1][p2];

	int l = 0, r = 1000;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (prova(mid))
			l = mid;
		else
			r = mid;
	}

	return prova(r) ? r : l;
}