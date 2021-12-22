#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<vector<pair<int, int>>> g(n);
	for (int i = 0, a, b; i < n-1; i++) {
		cin >> a >> b;
		a--, b--;
		g[a].push_back({b, 0});
		g[b].push_back({a, 1});
	}
	function<int(int, int)> dfs = [&](int v, int par) {
		int ans = 0;
		for (auto &[u, w] : g[v])
			if (u != par)
				ans += dfs(u, v) + w;
		return ans;
	};
	vector<int> dp(n);
	dp[0] = dfs(0, -1);
	function<void(int, int)> prop = [&](int v, int par) {
		for (auto &[u, w] : g[v]) {
			if (u != par) {
				dp[u] = dp[v] + (w ? -1 : 1);
				prop(u, v);
			}
		}
	};
	prop(0, -1);
	int ans = *min_element(dp.begin(), dp.end());
	vector<int> x;
	for (int i = 0; i < n; i++)
		if (dp[i] == ans)
			x.push_back(i+1);
	cout << ans << "\n";
	for (int i : x)
		cout << i << " ";
	cout << "\n";
}
