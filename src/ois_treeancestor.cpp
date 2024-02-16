#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	int n; cin >> n;
	int k; cin >> k;
	vector<vector<int>> adj(n);
	for (int i = 0, a, b; i < n - 1; ++i) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	vector<int> ans(n, -1);
	vector<int> st;
	auto dfs = [&](auto&& self, int v, int p) -> void {
		if ((int)st.size() >= k) {
			ans[v] = st[st.size() - k];
		}
		st.push_back(v);
		for (int u : adj[v]) {
			if (u == p) {
				continue;
			}
			self(self, u, v);
		}

		st.pop_back();
	};
	dfs(dfs, 0, -1);

	for (int i = 0; i < n; ++i) {
		cout << ans[i] << " \n"[i == n-1];
	}
}
