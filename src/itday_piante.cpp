#include "bits/stdc++.h"
using namespace std;

int pollice_verde(int n, vector<int> h) {
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		bool l = (i != 0 && h[i - 1] > h[i]);
		bool r = (i != n-1 && h[i + 1] > h[i]);
		ans += !(l || r);
	}
	return ans;
}
