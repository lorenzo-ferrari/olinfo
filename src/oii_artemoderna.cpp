#include "bits/stdc++.h"
using namespace std;

bool ordina(int n, vector<int> v, vector<int> &l) {
	l.clear();
	int cnt = 1;
	for (int i = 1; i < n; ++i) {
		if (v[i] > v[i - 1]) {
			l.push_back(cnt);
			cnt = 0;
		}
		++cnt;
	}
	l.push_back(cnt);

	for (int i = 0, acc = 0; i < (int)l.size(); ++i) {
		reverse(begin(v) + acc, begin(v) + acc + l[i]);
		acc += l[i];
	}

	return is_sorted(begin(v), end(v));
}
