#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, t;
	cin >> n >> t;
	vector<int> a(n);
	for (int &i : a)
		cin >> i;
	sort(a.begin(), a.end(), greater<int>());	
	unordered_map<int, int> mp;
	function <int(int)> find_nxt = [&](int v) {
		if (v >= t || v == -1) return -1;
		return mp.find(v) == mp.end() ? v : mp[v] = find_nxt(mp[v]);
	};
	int ans = 1e9;
	for (int i : a) {
		int x = find_nxt(i % t + 1); // nxt libero range (i%t, t)
		if (mp.find(i % t) == mp.end()) {
			ans = min(ans, i + t);
			mp[i % t] = x;
		}
		if (x == -1) {
			int y = find_nxt(0);
			if (y != -1)
				ans = min(ans, (i / t + 1) * t + y);
		}
		else
			ans = min(ans, (i / t) * t + x);
	}

	int x = find_nxt(0);
	if (x != -1)
		ans = min(ans, x);

	cout << ans << "\n";
}
