#include <bits/stdc++.h>
using namespace std;

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int64_t n;
	int64_t b;
	cin >> n >> b;

	vector <int64_t> p(n);

	for (int64_t &i : p)
		cin >> i;

	int64_t ans = 0;
	for (int64_t i = 0, l = 0, r = 0, tb = b; r < n; i++) {
		while (tb < 0)
			tb += p[i] - p[l++];

		while (r < n && p[r] - p[i] <= tb)
			tb -= p[r++] - p[i];

		while (r < n && l < r && p[i] - p[l] > p[r] - p[i]) {
			tb -= p[r++] - p[i];
			tb += p[i] - p[l++];

			while (r < n && p[r] - p[i] <= tb)
				tb -= p[r++] - p[i];
		}

		if (r - l > ans)
			ans = r - l;

		if (i != n - 1) {
			tb -= (p[i + 1] - p[i]) * (i - l + 1);
			tb += (p[i + 1] - p[i]) * (r - i - 1);
		}
	}

	cout << ans << "\n";
}
