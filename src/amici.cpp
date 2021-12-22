#include <vector>
#include <iostream>
#include <numeric>
#pragma GCC optimize ("O3")
using namespace std;
#define F first
#define S second

int N, K, T;
vector <int> t, pos;
vector <bool> vis;
vector <pair<int, int>> m;
vector <vector<int>> c;

void dfs(int v, int acc) {
	if (vis[v]) return;
	vis[v] = true;
	m[v] = {c.size() - 1, acc};
	c.back().push_back(v);

	dfs(t[pos[v]], acc + 1);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d%d%d", &N, &K, &T);

	t.resize(N + 1);
	m.resize(N + 1);
	c.resize(N + 1);
	pos.resize(N + 1);
	vis.resize(N + 1);

	iota(pos.begin(), pos.end(), 0);

	for (int i = 1; i <= N; i++)
		scanf("%d", &t[i]);

	vector <int> amici(K);
	for (int &i : amici) cin >> i;

	for (int i : amici) {
		if (!vis[i]) {
			c.push_back(vector<int>(0));
			dfs(i, 0);
		}
	}

	vector <bool> w(N + 1);
	for (int i : amici)
		w[c[m[i].F][(m[i].S + T) % c[m[i].F].size()]] = true;

	for (int i = 1; i <= N; i++) {
		if (w[i] && !w[(i - 2 + N) % N + 1]) {
			printf("%d\n", i);
			return 0;
		}
	}
}
