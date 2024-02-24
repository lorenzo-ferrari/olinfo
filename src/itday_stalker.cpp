#include "bits/stdc++.h"
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
using namespace std;
using LL = long long;

static constexpr LL INF = 1e15;

LL stalkera(int n, int k, vector<int> s) {
	vector<LL> prf(n+1);
	for (int i = 1; i <= n; ++i) {
		prf[i] = prf[i - 1] + s[i - 1];
	}
	map<LL, LL> m;
	auto insert = [&](LL x, LL y) -> void {
		auto it = m.lower_bound(x);
		it = prev(it);
		while (next(it) != end(m) && next(it)->second >= y) {
			m.erase(next(it));
		}
		if (it->second > y && !m.count(x)) {
			m[x] = y;
		}
	};
	auto works = [&](LL x) -> bool {
		m.clear();
		m[-INF] = INF;
		m[prf[n]] = 0;
		vector<LL> d(n+1, -1);
		for (int i = n-1; i >= 0; --i) {
			auto it = m.upper_bound(prf[i] + x);
			LL d = 1 + prev(it)->second;
			if (i == 0) {
				return d <= k;
			}
			if (d < k) {
				insert(prf[i], d);
			}
		}
		return false;
	};

	LL l = -INF, r = INF;
	while (r - l > 1) {
		LL m = (l + r) / 2;
		if (works(m)) {
			r = m;
		} else {
			l = m;
		}
	}
	return r;
}
