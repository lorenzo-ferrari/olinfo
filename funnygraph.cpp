#include <bits/stdc++.h>
using namespace std;

int64_t n, m;
vector <vector<array<int64_t, 3>>> g;

bool dfs(int64_t val) {
	vector <int64_t> p(n);
	vector <bool> vis(n);

	stack <int64_t> st;
	for (int64_t i = 0; i < n; i++) {
		if (!vis[i]) {
			vis[i] = true;
			st.push(i);
			while (!st.empty()) {
				int64_t v = st.top();
				st.pop();
				for (auto e : g[v]) {
					if (e[1] > val)
						break;
					if (vis[e[0]]) {
						if (p[v] - p[e[0]] != e[2])
							return false;
					}
					else {
						p[e[0]] = p[v] - e[2];
						vis[e[0]] = true;
						st.push(e[0]);
					}
				}
			}
		}
	}

	return true;
}

int64_t bs(int64_t l, int64_t r) {
	while (l < r - 1) {
		int64_t mid = l + (r - l) / 2;
		if (dfs(mid))
			l = mid;
		else
			r = mid;
	}

	return l;
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	g.resize(n);
	for (int64_t i = 0, a, b, z; i < m; i++) {
		cin >> a >> b >> z;
		g[a].push_back({b,i+1,z});
		g[b].push_back({a,i+1,-z});
	}

	cout << bs(0, m+1) << "\n";
}