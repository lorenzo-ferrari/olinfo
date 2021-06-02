#include <map>
#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;
#define int int64_t

#define F first
#define S second
const int N = 1e5;

int n;
int ans;
int v[N];

inline int solve(int l, int r) {
	if ((r - l) * (r - l) <= ans || l >= r)
		return 0;
	map <int, int> f;
	for (int i = l; i < r; i++)
		f[v[i]]++;
	int mn = f.begin()->S, mx = f.begin()->S;
	for (auto x : f) {
		mn = min(mn, x.S);
		mx = max(mx, x.S);
	}
	int res = mn * mx;
	int tl = l;
	for (int i = l; i < r; i++) {
		if (f[v[i]] == mn) {
			res = max(res, solve(tl, i));
			tl = i + 1;
		}
	}
	res = max(res, solve(tl, r));

	ans = max(ans, res);

	return res;
}

int32_t main() {
	scanf("%ld", &n);
	for (int i = 0; i < n; i++) scanf("%ld", v + i);

	printf("%ld\n", solve(0, n));
}
