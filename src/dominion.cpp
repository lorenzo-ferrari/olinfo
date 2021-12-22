#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define F first
#define S second

#define N 100000

int main() {
	int n, m, t;
	scanf("%d%d%d", &n, &m, &t);

	int a[N], p[N], r[N], v[N];
	deque <int> d;
	map <int, pair<int, int>> p_to_idx;

	for (int c; m--;) {
		scanf("%d", &c);
		d.push_back(c);
	}

	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d", a+i, p+i, r+i, v+i);
		if (a[i]) p_to_idx[p[i]] = {a[i], i};
	}

	int mano[5];
	for (int b = 0; t--; b = 0) {
		for (int c = 0; c < 5; c++) {
			mano[c] = d.front();
			d.pop_front();
			b += r[mano[c]];
		}
		auto it = p_to_idx.lower_bound(b);
		if (it->F > b) it--;
		while (it->S.F <= 0)
			it--;
		it->S.F--;
		d.push_back(it->S.S);

		if (it->S.F == 0)
			p_to_idx.erase(it);

		for (int c = 0; c < 5; c++) {
			d.push_back(mano[c]);
		}
	}

	int ans = 0;
	for (int &i : d)
		ans += v[i];

	printf("%d\n", ans);
}
