#include "bits/stdc++.h"
using namespace std;

bool heights(int n, vector<int> z, vector<int>& h) {
	h[0] = z[0], h[n - 1] = z[n - 2];
	for (int i = 1; i < n - 1; ++i) {
		if (h[i - 1] == z[i - 1]) {
			h[i] = min(z[i - 1], z[i]);
		} else {
			if (z[i - 1] <= z[i]) {
				h[i] = z[i - 1];
			} else {
				return false;
			}
		}
	}
	return true;
}
