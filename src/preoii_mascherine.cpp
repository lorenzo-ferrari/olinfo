#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define F first
#define S second

void riprogramma(int n, int k, vector <int> &c) {
	if (k == 2) {
		int m1 = 0, m2 = 0;
		for (int i = 0; i < n; i++) {
			m1 += ((i & 1) == (c[i] & 1));
			m2 += ((i & 1) != (c[i] & 1));
		}
		if (m1 < m2) {
			for (int i = 0; i < n; i++)
				c[i] = ((i & 1) + 1);
		} else {
			for (int i = 0; i < n; i++)
				c[i] = (((i + 1) & 1) + 1);
		}
		return;
	}

	vector <pair<int, int>> v;
	for (int i : c) {
		if (v.empty() || v.back().F != i)
			v.push_back({i, 1});
		else
			v.back().S++;
	}

	for (int acc = 0, j = 0; j < v.size(); j++) {
		if (v[j].S > 1) {
			int col = 1;
			while (col == v[j].F || (j < v.size() - 1 && col == v[j + 1].F))
				col++;
			assert(col <= k);
			for (int k = 1; k < v[j].S; k += 2) {
				c[acc + k] = col;
			}
		}

		acc += v[j].S;
	}
}