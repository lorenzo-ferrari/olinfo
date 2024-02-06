#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr int N = 200000;
static constexpr int BS = 512;
static constexpr LL mod = 1e9 + 7;

LL fxp(LL x, LL y) {
	LL ans = 1;
	while (y) {
		if (y & 1) {
			ans = ans * x % mod;
		}
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}
LL get_inv(LL x) { return fxp(x, mod - 2); }

struct item {
	int cnt;
	LL prd;
	item() : cnt(0), prd(1) {}
};

struct SQRT {
	vector<item> blocks;
	vector<LL> vals;
	SQRT() : blocks(N / BS + 1), vals(N + BS) {}
	void insert(int i, LL val) {
		vals[i] = val;
		blocks[i / BS].cnt += 1;
		blocks[i / BS].prd *= val;
		blocks[i / BS].prd %= mod;
	}
	void erase(int i, LL inv) {
		vals[i] = 0;
		blocks[i / BS].cnt -= 1;
		blocks[i / BS].prd *= inv;
		blocks[i / BS].prd %= mod;
	}
	LL get(int k) {
		LL ans = 1;
		int b = N / BS;
		for (; b >= 0 && k >= blocks[b].cnt; --b) {
			k -= blocks[b].cnt;
			ans *= blocks[b].prd;
			ans %= mod;
		}
		for (int i = (b + 1) * BS - 1; k > 0; --i) {
			if (vals[i] != 0) {
				--k;
				ans = ans * vals[i] % mod;
			}
		}
		return ans;
	}
};

int main() {
	int n; cin >> n;
	int q; cin >> q;
	vector<LL> a(n), inv(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		inv[i] = get_inv(a[i]);
	}
	vector<int> p(n);
	{
		vector<int> t(n);
		iota(begin(t), end(t), 0);
		sort(begin(t), end(t), [&](int i, int j){
			return a[i] < a[j];
		});
		for (int i = 0; i < n; ++i) {
			p[t[i]] = i;
		}
	}
	vector<array<int, 4>> qq(q);
	for (int i = 0, l, r, k; i < q; ++i) {
		cin >> l >> r >> k;
		qq[i] = {l, r, k, i};
	}
	sort(begin(qq), end(qq), [&](array<int, 4> a, array<int, 4> b){
		if (a[0] / BS == b[0] / BS) {
			return a[1] < b[1];
		} else {
			return a[0] < b[0];
		}
	});

	SQRT s;
	vector<int> ans(q);
	int cl = 0, cr = -1;
	for (auto [l, r, k, i] : qq) {
		while (cr < r) { ++cr; s.insert(p[cr], a[cr]); }
		while (cr > r) { s.erase(p[cr], inv[cr]); --cr; }
		while (cl < l) { s.erase(p[cl], inv[cl]); ++cl; }
		while (cl > l) { --cl; s.insert(p[cl], a[cl]); }
		ans[i] = s.get(k);
	}

	for (int i = 0; i < q; ++i) {
		cout << ans[i] << "\n";
	}
}
