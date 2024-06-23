#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	static constexpr int M = 1e6;
	vector<int> d(M + 1);
	for (int p = 2; p <= M; ++p) {
		if (d[p] != 0) continue;
		for (int i = p; i <= M; i += p) {
			if (d[i] == 0) {
				d[i] = p;
			}
		}
	}

	auto factor = [&](int n) -> map<int, int> {
		assert(n <= M);
		map<int, int> ans;
		while (n != 1) {
			int p = d[n];
			int cnt = 0;
			while (d[n] == p) {
				++cnt;
				n /= p;
			}
			if (cnt % 4) {
				ans[p] = cnt % 4;
			}
		}
		return ans;
	};
	auto complement = [&](map<int, int> m) -> map<int, int> {
		for (auto& [p, e] : m) {
			assert(0 < e && e < 4);
			e = 4 - e;
		}
		return m;
	};
	auto expand = [&](map<int, int> m) -> LL {
		LL ans = 1;
		for (auto [p, e] : m) {
			while (e--) {
				ans *= p;
			}
		}
		return ans;
	};
	auto add = [&](map<int, int> m1, map<int, int> m2) -> map<int, int> {
		for (auto [p, e] : m1) {
			m2[p] += e;
			m2[p] %= 4;
			if (m2[p] == 0) {
				m2.erase(p);
			}
		}
		return m2;
	};

	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	vector<map<int, int>> ms(n);
	for (int i = 0; i < n; ++i) {
		ms[i] = factor(a[i]);
	}

	LL ans = 0;
	map<LL, int> frq;

	for (int i = 1; i+2 < n; ++i) {
		for (int j = 0; j < i; ++j) {
			++frq[expand(add(ms[i], ms[j]))];
		}
		for (int j = i+2; j < n; ++j) {
			ans += frq[expand(complement(add(ms[i+1], ms[j])))];
		}
	}

	cout << ans << "\n";
}
