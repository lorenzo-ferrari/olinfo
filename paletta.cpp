#include <iostream>
#pragma GCC optimize ("O3")

const int N = 1500042;
int t[2][N];

void inc(int n, int idx, int b) {
	for (; idx < n; idx = idx | (idx + 1))
		t[b][idx]++;
}

int query(int r, int b) {
  	int ans = 0;
  	for (; r >= 0; r = (r & (r + 1)) - 1)
		ans += t[b][r];
  	return ans;
}

long long paletta_sort(int n, int v[]) {
  long long ans = 0;

  for (int i = n - 1; i >= 0; i--) {
    if ((i & 1) != (v[i] & 1)) return -1;
    ans += (i >> 1) - (v[i] >> 1) + query(v[i], i & 1);
    inc(n, v[i], i & 1);
  }

  return ans;
}