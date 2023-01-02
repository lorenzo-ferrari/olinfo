#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define F first
#define S second

const int N = 1e5 + 5;
const int LOG = 20;

long long mst;

int dep[N];
pair<int, int> up[N][LOG];

pair<int, int> choose(pair<int, int> a, pair<int, int> b) {
	return {b.F, max(a.S, b.S)};
}

void init(int n, vector<vector<pair<int, int>>> g) {
	function<void(int, int)> dfs = [&](int v, int par) {
		for (auto &[a, b] : g[v]) {
			if (a ^ par) {
				dep[a] = dep[v] + 1;
				up[a][0] = {v, b};
				dfs(a, v);
			}
		}
	};
	dfs(0, 0);
	for (int i = 1; i < LOG; i++)
		for (int j = 0; j < n; j++)
			up[j][i] = choose(up[j][i-1], up[up[j][i-1].F][i-1]);
}

int lca(int u, int v) {
	if (dep[u] > dep[v])
		swap(v, u);
	int k = dep[v] - dep[u];
	for (int i = LOG-1; i >= 0; i--)
		if (k & (1 << i))
			v = up[v][i].F;
	if (u == v)
		return u;
	for (int i = LOG-1; i >= 0; i--)
		if (up[v][i].F != up[u][i].F) {
			v = up[v][i].F;
			u = up[u][i].F;
		}
	return up[u][0].F;
}

int mx(int v, int k) {
	int ans = 0;
	for (int i = LOG-1; i >= 0; i--)
		if (k & (1 << i)) {
			ans = max(ans, up[v][i].S);
			v = up[v][i].F;
		}
	return ans;
}

int query(int a, int b) {
	int l = lca(a, b);
	return max(mx(a, dep[a] - dep[l]), mx(b, dep[b] - dep[l]));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> m >> n;

	vector<array<int, 3>> ed;
	for (int i = 0, a, b, c; i < m; i++) {
		cin >> a >> b >> c;
		ed.push_back({a, b, c});		
	}

	auto x = ed;
	sort(ed.begin(), ed.end(), [&](array<int, 3> &a, array<int, 3> &b){return a[2] < b[2];});

	vector<int> p(n);
	iota(p.begin(), p.end(), 0);

	function<int(int)> find_set = [&](int v) {
		return p[v] == v ? v : p[v] = find_set(p[v]);
	};
	function<bool(int, int)> union_set = [&](int a, int b) {
		a = find_set(a);
		b = find_set(b);
		if (a ^ b) {
			p[b] = a;
			return true;
		}
		return false;
	};

	vector<vector<pair<int, int>>> t(n);
	for (auto &[a, b, c] : ed) {
		if (union_set(a, b)) {
			mst += c;
			t[a].push_back({b, c});
			t[b].push_back({a, c});
		}
	}

	init(n, t);

	for (auto &[a, b, c] : x) {
		cout << mst - query(a, b) + c << "\n";
	}
}
