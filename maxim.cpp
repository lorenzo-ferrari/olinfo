#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

int n, k;
int t[2 * N];

void build() {
	for (int i = n-1; i > 0; i--)
		t[i] = max(t[i << 1], t[i << 1 | 1]);
}

int query(int l, int r) {
	int ans = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1) ans = max(ans, t[l++]);
		if (r & 1) ans = max(ans, t[--r]);
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;
	vector <int> g(n);
	for (int i = 0; i < n; i++) {
		cin >> g[i];
		t[i + n] = g[i];
	}

	build();

	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans = max(ans, query(max(0, i-k), min(n, i+k+1)) - g[i]);
	}

	cout << ans << "\n";
}
