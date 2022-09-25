#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define F first
#define S second

const int N = 1e5;

bool vis[N];
vector <int> ord;
vector <int> g[N];
vector <int> t[N];

void dfs(int v) {
	vis[v] = true;
	for (int u : g[v]) {
		if (!vis[u]) {
			t[v].push_back(u);
			dfs(u);
		}
	}

	ord.push_back(v);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n;
	cin >> n;
	for (int i = 0, a, b; i < n-1; ++i) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	dfs(0);

	int ans = 0;

	int d1[N] {};
	int d2[N] {};
	for (int v : ord) {
		for (int u : t[v]) {
			if (d1[u] + 1 >= d1[v]) {
				d2[v] = d1[v];
				d1[v] = d1[u] + 1;
 			}
			else if (d1[u] + 1 > d2[v]) {
				d2[v] = d1[u] + 1;
			}
		}
		ans = max(ans, d1[v] + d2[v]);
	}

	cout << 2*ans << "\n";
}
