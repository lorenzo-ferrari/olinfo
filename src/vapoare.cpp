#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define F first
#define S second

const int N = 1e5;

int sets;
int p[N];

int find_set(int v) {
	return (v == p[v]) ? v : p[v] = find_set(p[v]);
}

void union_set(int a, int b) {
	a = find_set(a);
	b = find_set(b);

	if (a != b) {
		p[b] = a;
		sets--;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, k, t;
	cin >> n >> k >> t;
	sets = n;
	vector <array<int, 3>> e(k);
	for (int i = 0; i < n; i++) p[i] = i;
	for (int i = 0, a, b, w; i < k; i++) {
		cin >> a >> b >> w;
		e[i] = {w, a, b};
	}

	vector <pair<int, int>> g(t);
	for (int i = 0, v; i < t; i++) {
		cin >> v;
		g[i] = {v, i};
	}

	sort(e.begin(), e.end());
	sort(g.begin(), g.end());

	vector <int> ans(t);
	for (int i = t - 1, j = k - 1; i >= 0; i--) {
		while (j >= 0 && e[j][0] >= g[i].F) {
			union_set(e[j][1], e[j][2]);
			j--;
		}
		ans[g[i].S] = sets;
	}

	for (int i : ans) cout << i << "\n";
}
