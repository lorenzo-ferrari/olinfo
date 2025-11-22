#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int m; cin >> m;
	int k; cin >> k;
	string s; cin >> s;
	vector<LL> pows(m + 1, 1);
	for (int i = 1; i <= m; ++i)
		pows[i] = 10LL * pows[i - 1] % k;
	auto eval = [&](string s) -> LL {
		LL ans = 0;
		for (int i = 0; i < (int)s.size(); ++i) {
			ans += pows[i] * (s[s.size() - 1 - i] - '0');
			ans %= k;
		}
		return ans;
	};
	vector<string> mods(k, "");
	sort(begin(s), end(s), greater<char>());
	do {
		LL val = eval(s);
		if (mods[val] == "") {
			mods[val] = s;
		} else {
			cout << s << "\n" << mods[val] << "\n";
			return 0;
		}
	} while (prev_permutation(begin(s), end(s)) && s[0] != '0');

	cout << "-1\n";
}
