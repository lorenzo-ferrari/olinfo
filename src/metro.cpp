#include <vector>
#include <iostream>
#include <algorithm>
#pragma GCC optimize ("O3")
using namespace std;
#define int int64_t

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	char c;

	cin >> n;
	vector <bool> s(n), t(n);
	for (int i = 0; i < n; i++) {cin >> c; s[i] = (c == '^');}
	for (int i = 0; i < n; i++) {cin >> c; t[i] = (c == 'v');}
	reverse(t.begin(), t.end());

	cin >> m;
	vector <bool> r(m);
	for (int i = 0; i < m; i++) {cin >> c; r[i] = (c == '<');}

	const int K = 7;
	const int MOD = 1e9 + 9;
	const int inv = 857142865; // pow(7, MOD - 2) % MOD;

	vector <int> p(m); p[0] = 1;
	for (int i = 1; i < m; i++) p[i] = (p[i - 1] * K) % MOD;

	int ans = 0, hash_value1 = 0, hash_value2 = 0, target = 0;

	for (int i = 0; i < m; i++) if (r[i]) target = (target + p[i]) % MOD;

	for (int i = 0; i < m; i++) {
		if (s[i]) hash_value1 = (hash_value1 + p[i]) % MOD;
		if (t[i]) hash_value2 = (hash_value2 + p[i]) % MOD;
	}

	ans += (hash_value1 == target);
	ans += (hash_value2 == target);

	for (int i = m; i < n; i++) {
		if (s[i - m]) hash_value1 = (hash_value1 - 1 + MOD) % MOD;
		if (t[i - m]) hash_value2 = (hash_value2 - 1 + MOD) % MOD;

		hash_value1 = (hash_value1 * inv) % MOD;
		hash_value2 = (hash_value2 * inv) % MOD;

		if (s[i]) hash_value1 = (hash_value1 + p[m - 1]) % MOD;
		if (t[i]) hash_value2 = (hash_value2 + p[m - 1]) % MOD;

		ans += (hash_value1 == target);
		ans += (hash_value2 == target);
	}

	cout << ans << "\n";
}
