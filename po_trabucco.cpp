#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define F first
#define S second

const int N = 2000;
const int MOD = 1e9 + 7;

int _n, _m;
int d[N][N];
int dp[N][N];

bool possible(int val) {
	if (d[0][0] < val)
		return false;

	bitset <N> vis[N];
	vis[0][0] = true;

	for (int i = 1; i < _n; i++) {
		if (d[i][0] >= val)
			vis[i][0] = true;
		else
			break;
	}
	for (int i = 1; i < _m; i++) {
		if (d[0][i] >= val)
			vis[0][i] = true;
		else
			break;
	}

	for (int i = 1; i < _n; i++)
		for (int j = 1; j < _m; j++)
			if (d[i][j] >= val && (vis[i-1][j] || vis[i][j-1]))
				vis[i][j] = 1;

	return vis[_n-1][_m-1];
}

void fill_d(int k, int* x, int* y) {
	for (int i = 0; i < _n; i++)
		for  (int j = 0; j < _m; j++)
			d[i][j] = 3*N;

	queue <pair<int, int>> Q;
	for (int i = 0; i < k; i++) {
		d[x[i]][y[i]] = 0;
		Q.push({x[i], y[i]});
	}

	while (!Q.empty()) {
		int tx = Q.front().F;
		int ty = Q.front().S;

		Q.pop();

		if (tx != 0 && d[tx-1][ty] > d[tx][ty] + 1) {
			d[tx-1][ty] = d[tx][ty] + 1;
			Q.push({tx-1, ty});
		}
		if (ty != 0 && d[tx][ty-1] > d[tx][ty] + 1) {
			d[tx][ty-1] = d[tx][ty] + 1;
			Q.push({tx, ty-1});
		}
		if (tx != _n-1 && d[tx+1][ty] > d[tx][ty] + 1) {
			d[tx+1][ty] = d[tx][ty] + 1;
			Q.push({tx+1, ty});
		}
		if (ty != _m-1 && d[tx][ty+1] > d[tx][ty] + 1) {
			d[tx][ty+1] = d[tx][ty] + 1;
			Q.push({tx, ty+1});
		}
	}
}

int ContaPercorsi(int n, int m, int k, int* x, int* y) {
	_n = n; _m = m;
	fill_d(k,x,y);

	int l = 0, r = N, mid;
	while (l < r-1) {
		mid = l + (r-l)/2;
		if (possible(mid))
			l = mid;
		else
			r = mid;
	}

	int sec = l;

	dp[0][0] = 1;
	for (int i = 1; i < n; i++) {
		if (d[i][0] >= sec)
			dp[i][0] = 1;
		else
			break;
	}

	for (int i = 1; i < m; i++) {
		if (d[0][i] >= sec)
			dp[0][i] = 1;
		else
			break;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (d[i][j] >= sec) {
				dp[i][j] = dp[i-1][j] + dp[i][j-1];
				if (dp[i][j] >= MOD)
				    dp[i][j] -= MOD;
			}
		}
	}

	return dp[n-1][m-1];
}