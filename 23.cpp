#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define F first
#define S second

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	vector<pair<int, int>> a(n);
	for (int i = 0, x; i < n; i++) {
		cin >> x;
		a[i] = {x, i};
	}
	sort(a.begin(), a.end());

	vector<int> ans(n);
	int res = 0, s2 = 0, s3 = 0;
	for (int i = 1, idx = 0; i <= a.back().F; i++) {
		++s2, ++s3;
		int t2 = i, t3 = i;
		while (t2 % 2 == 0 && t2)
			s2 -= 1, t2 /= 2;
		while (t3 % 3 == 0 && t3)
			s3 -= 2, t3 /= 3;
		res += (s2 == s3);
		while (idx < n && i == a[idx].F) {
			ans[a[idx].S] = res;
			idx++;
		}
	}

	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << "\n";
}
