#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	map<int, LL> cnt;
	int n; cin >> n;
	LL ans = 0;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		int y; cin >> y;
		ans += cnt[y - x];
		++cnt[y - x];
	}
	cout << ans << "\n";
}
