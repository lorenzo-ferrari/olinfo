#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int64_t n, f;
vector <int64_t> k;

bool possible(int64_t val) {
	for (int64_t i = 1, pl = 1, prv = k[0]; i < n;) {
		while (i < n && k[i] - prv < val)
			i++;
		if (i < n) {
			pl++;
			prv = k[i];
		}

		if (pl == f)
			return true;
	}

	return false;
}

int main() {
	#ifdef EVAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	scanf("%ld%ld", &n, &f);
	k.resize(n);
	for (int64_t &i : k)
		scanf("%ld", &i);

	int64_t l = 0, r = k.back();
	while (l < r - 1) {
		int64_t mid = l + (r - l) / 2;
		if (possible(mid))
			l = mid;
		else
			r = mid;
	}

	printf("%ld\n", l);
}
