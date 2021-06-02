#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int N = 1e5;

int ans, t;
int v[N], val[N], tme[N];
bitset <N> vis;

void dfs(int i, int tv) {
	if (vis[i]) {
		if (tme[i] == t)
			ans = max(ans, tv - val[i]);
	} else {
		vis[i] = true;
		val[i] = tv;
		tme[i] = t;
		dfs(v[i], tv + 1);
	}
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> v[i];

	t = 1;
	for (int i = 0; i < n; i++, t++) {
		if (!vis[i])
			dfs(i, 0);
	}

	cout << ans << "\n";
}
