#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int s[1000001];
bool p(int &n, int &m, int t[], int mid) {
	fill(s, s+m, 0);
	s[0] = mid;
	for (int i = 0, j = 0; i <= m; i++) {
		for (int k = 0; j < n && k < s[i]; k++, j++) {
			if (i + t[j] > m)
				return false;
			s[i + t[j]]++;
		}
	}

	return true;
}

int gpu(int n, int m, int t[]) {
	int l = 0, r = n, mid;
	while (l < r - 1) {
		mid = (l + r) / 2;
		if (p(n, m, t, mid))
			r = mid;
		else
			l = mid;
	}

	return r;
}