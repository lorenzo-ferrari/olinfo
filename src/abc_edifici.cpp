#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define F first
#define S second

const int N = 5000;
const int INF = 2e9;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n, m, k;
	cin >> n >> m >> k;

	vector <int> sedi(k);
	for (int &i : sedi) {
		cin >> i;
		--i;
	}

	vector <vector<pair<int, int>>> g(n);
	for (int i = 0, a, b, l; i < m; ++i) {
		cin >> a >> b >> l;
		--a, --b;
		g[a].push_back({b, l});
		g[b].push_back({a, l});
	}

	vector <vector<int>> d(k, vector <int> (n, INF));
	priority_queue <pair<int, int>> Q;
	for (int i = 0; i < k; ++i) {
		bitset <N> vis;
		d[i][sedi[i]] = 0;
		Q.push({0, sedi[i]});

		while (!Q.empty()) {
			int v = Q.top().S;
			Q.pop();

			if (vis[v])
				continue;
			vis[v] = true;

			for (auto e : g[v]) {
				if (d[i][e.F] > d[i][v] + e.S) {
					d[i][e.F] = d[i][v] + e.S;
					Q.push({-d[i][e.F], e.F});
				}
			}
		}
	}

	vector <int> p(k);
	iota(p.begin(), p.end(), 0);

	int ans = INF;
	do {
		for (int i = 0; i < n; ++i) {
			if (find(sedi.begin(), sedi.end(), i) != sedi.end())
				continue;

			int tans = d[p[0]][i] + d[p[k-1]][i];
			for (int j = 0; j < k-1; ++j)
				tans += d[p[j]][sedi[p[j + 1]]];
			ans = min(ans, tans);
		}
	} while (next_permutation(p.begin(), p.end()));

	cout << ans << "\n";
}
