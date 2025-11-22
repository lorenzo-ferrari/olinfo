#include "bits/stdc++.h"
using namespace std;
using LL = long long;

LL carica(int n, int k, vector<int> a) {
	LL cost = k + a[n - 1], sum = a[n - 1];
	for (int i = 0; i < n - 1; ++i) {
		sum += a[i];
		cost += min(a[i], k);
	}

	return min(cost, sum);
}
