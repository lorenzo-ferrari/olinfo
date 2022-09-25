#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

void solve() {
	int n, k;
	cin >> n >> k;
	vector <long double> p(n);

	long double ans = 0;
	priority_queue <pair<long double, int>> Q;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		Q.push({p[i], i});
	}

	while (k--) {
		long double cur_p = Q.top().first;
		int i = Q.top().second;
		Q.pop();

		ans += cur_p;
		Q.push({cur_p * (1.0 - p[i]), i});
	}

	cout << fixed << setprecision(6) << floor(ans * 1000000) / 1000000 << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}
