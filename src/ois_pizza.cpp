#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	int n; cin >> n;
	int m; cin >> m;
	int q; cin >> q;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i] >> b[i];
	}
	vector<int> src(m);
	for (int i = 0, k; i < m; ++i) {
		cin >> k;
		for (int j = 0; j < k; ++j) {
			int p; cin >> p;
			src[i] |= (1 << p);
		}
	}
	vector<LL> d(1 << n, 1e15);
	priority_queue<array<LL, 2>> Q;
	for (int i = 0; i < m; ++i) {
		d[src[i]] = 0;
		Q.push({0, src[i]});
	}
	while (!Q.empty()) {
		auto [td, v] = Q.top();
		Q.pop();
		if (-td < d[v])
			continue;
		for (int i = 0; i < n; ++i) {
			int oth = v ^ (1 << i);
			LL newd = d[v] + ((v & (1 << i)) ? b[i] : a[i]);
			if (d[oth] > newd) {
				d[oth] = newd;
				Q.push({-newd, oth});
			}
		}
	}
	for (int i = 0, k; i < q; ++i) {
		cin >> k;
		int id = 0;
		for (int j = 0; j < k; ++j) {
			int p; cin >> p;
			id |= (1 << p);
		}
		cout << d[id] << "\n";
	}
}
