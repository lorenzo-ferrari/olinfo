#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int g, n;
	cin >> g >> n;

	string sg;
	string sn;
	cin >> sg >> sn;

	int missing = 0;
	int fg[128] {};
	for (char c : sg)
		missing += (fg[c]++ == 0);

	int ans = 0;
	int fn[128] {};
	for (int i = 0; i < g; i++) {
		fn[sn[i]]++;
		missing -= (fn[sn[i]] == fg[sn[i]]);
		missing += (fn[sn[i]] - 1 == fg[sn[i]]);
	}

	ans += (missing == 0);

	for (int i = g; i < n; i++) {
		fn[sn[i]]++;
		missing -= (fn[sn[i]] == fg[sn[i]]);
		missing += (fn[sn[i]] - 1 == fg[sn[i]]);

		fn[sn[i - g]]--;
		missing -= (fn[sn[i - g]] == fg[sn[i - g]]);
		missing += (fn[sn[i - g]] + 1 == fg[sn[i - g]]);

		ans += (missing == 0);
	}

	cout << ans << "\n";
}
