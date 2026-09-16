#include "bits/stdc++.h"
using namespace std;
using LL = long long;

vector<int> verifica(int n, vector<int> t) {
	vector<array<int, 2>> v(n);
	for (int i = 0; i < n; ++i)
		v[i] = {t[i], i};

	sort(begin(v), end(v));

	int l = v[0][1];
	int r = v[0][1];

	vector<array<int, 2>> lrs;
	for (int i = 1; i < n; ++i) {
		int nl = min(l, v[i][1]);
		int nr = max(r, v[i][1]);

		if (array<int, 2>{nl, nr} != array<int, 2>{l, r})
			lrs.push_back({nl, nr});

		l = nl;
		r = nr;
		if (r - l > v[i][0])
			return {};
	}

	reverse(begin(lrs), end(lrs));

	l = v[0][1];
	r = v[0][1];
	vector<int> ans;
	ans.push_back(l);
	for (; !lrs.empty(); lrs.pop_back()) {
		while (l > lrs.back()[0])
			ans.push_back(--l);
		while (r < lrs.back()[1])
			ans.push_back(++r);
	}

	return ans;
}
