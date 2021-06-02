#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

void Colora(int n, int q, vector <int> &a, vector <int> &b, vector <int> &c, vector <int> &murale) {
	int nxt[900000];
	bool vis[900000]{};
	// vector <bool> vis(n);

	for (int i = 0; i < n; ++i)
		nxt[i] = i + 1;

	int l, r, tl;
	while (q--) {
		int l = a[q];
		int r = b[q];
		int tl;

		while (l <= r) {
			tl = nxt[l];

			nxt[l] = nxt[r];
			if (!vis[l]) {
				murale[l] = c[q];
				vis[l] = true;
			}

			l = tl;
		}
	}
}