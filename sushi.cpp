#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int sushi(int n, int b, vector <int> ta) {
	map <int, int> a;
	bitset <100001> dp;

	for (int &i : ta)
		a[i]++;
	dp[b] = 1;

	int er[10000], i0 = 0;
	for (int ans = 0; !a.empty(); ans++) {
		if (dp[0])
			return ans;

		for (auto &x : a) {
			int i = x.first, t = x.second;
			if (ans*t*i >= b)
				er[i0++] = i;
			else
				while (t--)
					dp |= dp >> i;
		}

		while (i0)
			a.erase(er[--i0]);
	}

	return -1;
}