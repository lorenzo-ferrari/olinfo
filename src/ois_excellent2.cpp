#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;
static constexpr int LG = 60;

int main() {
	auto combine = [&](array<LL, 3> a, array<LL, 3> b) {
		array<LL, 3> ans{};
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				ans[(i + j) % 3] += a[i] * b[j];
			}
		}
		for (int i = 0; i < 3; ++i) {
			ans[i] %= mod;
		}
		return ans;
	};
	array<LL, 3> p[LG];
	p[0] = {0, 1, 1};
	for (int i = 1; i < 60; ++i) {
		p[i] = combine(p[i - 1], p[i - 1]);
	}
	int t; cin >> t;
	while (t--) {
		LL n; cin >> n;
		array<LL, 3> ans{1, 0, 0};
		for (int i = 0; i < LG; ++i) {
			if (n & 1) {
				ans = combine(ans, p[i]);
			}
			n /= 2;
		}
		cout << ans[0] << "\n";
	}
}
