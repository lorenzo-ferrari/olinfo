// @check-accepted: *
// Time complexity: O(N sqrt (N log N) invack(N))
// Just like the optimal one, but max_k(n) works in O(N invack(N))
// For simplicity, assume all the endpoints are distinct.
// ...

#include <array>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr int THRESHOLD = 883;

struct Dsu {
	vector<int> p, s, m;
	Dsu(int n) : p(n), s(n, 1), m(n) {
		iota(begin(p), end(p), 0);
		iota(begin(m), end(m), 0);
	}
	int find(int v) {
		return p[v] == v ? v : p[v] = find(p[v]);
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b)
			return;
		if (s[a] < s[b])
			swap(a, b);
		p[b] = a;
		s[a] += s[b];
		m[a] = min(m[a], m[b]);
	}
	int getmin(int i) {
		return m[find(i)];
	}
};

int radioline(int n, vector<int> l, vector<int> r) {
	{ // make all the endpoints distinct, without affecting the answer
		vector<array<int, 3>> z(2 * n);
		for (int i = 0; i < n; ++i) z[i  ] = {l[i], 0, i};
		for (int i = 0; i < n; ++i) z[i+n] = {r[i], 1, i};
		sort(begin(z), end(z));
		for (int i = 0; i < 2 * n; ++i) {
			if (z[i][1] == 0)
				l[z[i][2]] = i;
			else
				r[z[i][2]] = i;
		}
	}

	vector<int> idxs(n);
	iota(begin(idxs), end(idxs), 0);
	sort(begin(idxs), end(idxs), [&](int i, int j){ return r[i] < r[j]; });
	
	vector<int> cache(n + 1, -1);
	auto max_k = [&](int m) -> int {
		// return max{k : one can form k subsets of m elements each}
		if (cache[m] != -1)
			return cache[m];
		Dsu dsu(2 * n);
		int k = 0;
		int last_r = -1, prv_r = -1;
		// devo davvero contarle? non basta m = #{intervalli considerati} - #{merge fatti} ?
		int cc = 0;
		for (int i : idxs) {
			if (l[i] <= last_r)
				continue;
			++cc;
			for (int j = prv_r + 1; j < r[i]; ++j)
				dsu.merge(j, r[i]);
			if (dsu.getmin(l[i]) != last_r + 1) {
				--cc;
				dsu.merge(l[i], dsu.getmin(l[i]) - 1);
			}
			if (cc >= m) {
				++k;
				cc = 0;
				last_r = r[i];
			}
			prv_r = r[i];
		}
		return cache[m] = k;
	};

	int ans = 1;
	for (int m = 1; m <= min(n, THRESHOLD); ++m)
		ans = max(ans, m * max_k(m));
	for (int k = 1; k <= n / THRESHOLD; ++k) {
		int ll = 0, rr = n + 1;
		while (rr - ll > 1) {
			int m = (ll + rr) / 2;
			if (max_k(m) >= k)
				ll = m;
			else
				rr = m;
		}
		ans = max(ans, k * ll);
	}

	return ans;
}
