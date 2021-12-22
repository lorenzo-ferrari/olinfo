#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;

bool p(int n, int a[], int b[], int val) {
	for (int i = 1, prv = a[0]; i < n; i++) {
		if (b[i] < prv + val)
			return false;
		else
			prv = max(a[i], prv + val);
	}

	return true;
}

void pianifica(int n, int a[], int b[], int t[]) {
	uint32_t l = 1, r = 2e9, mid;
	bool p;
	while (l < r - 1) {
		mid = (l + r) >> 1;
		p = true;
		for (uint32_t i = 1, prv = a[0]; i < n; i++) {
			if (b[i] < prv + mid) {
				p = false;
				break;
			} else {
				prv = max((uint32_t)a[i], prv + mid);
			}
		}

		if (p) l = mid;
		else r = mid;
	}

	t[0] = a[0];
	for (int i = 1; i < n; i++)
		t[i] = max(a[i], t[i - 1] + (int)l);
}