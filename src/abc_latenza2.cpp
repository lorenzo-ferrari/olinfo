#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define F first
#define S second

const int INF = 1e9;
const int MAXN = 2001;

int d[MAXN][MAXN];
int latenza(int N, int M, int A[], int B[], int L[]) {
	vector <vector<pair<int, int>>> g (N + 1);
	for (int i = 0; i < M; ++i) {
		g[A[i]].push_back({B[i], L[i]});
		g[B[i]].push_back({A[i], L[i]});
	}

	int d[MAXN][MAXN];
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; j++)
			if (i ^ j) d[i][j] = INF;

	int ans = 0;
	priority_queue <pair<int, int>> Q;
	for (int i = 1; i <= N; i++) {
		bitset <MAXN> vis;
		Q.push({0, i});

		while (!Q.empty()) {
			int v = Q.top().S;
			int l =-Q.top().F;
			Q.pop();

			if (vis[v])
				continue;
			vis[v] = true;

			for (auto e : g[v]) {
				if (d[i][e.F] > l + e.S) {
					d[i][e.F] = l + e.S;
					Q.push({-d[i][e.F], e.F});
				}
			}
		}

		for (int j = 1; j <= N; ++j)
			ans = max(ans, d[i][j]);
	}

	return ans;
}