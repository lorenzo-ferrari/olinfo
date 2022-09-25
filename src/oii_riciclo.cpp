#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL riciclo(int n, int m, vector<int> t, vector<int> p) {
  vector<LL> cnt(32);
  for (int i = 0; i < n; ++i) {
    LL x = t[i];
    for (int bit = 0; x > 0; x >>= 1, ++bit)
      cnt[bit] += x & 1;
  }

  LL ans = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = i; p[i] && j < 32; ++j) {
      LL psb = min(LL(p[i]), cnt[j] << (j-i));
      ans += psb;
      p[i] -= psb;
      LL tmp = (cnt[j] << j) - (psb << i);
      cnt[j] = 0;
      for (int bit = 0; tmp > 0 && bit < j; tmp >>= 1, ++bit)
        cnt[bit] += tmp & 1;
      cnt[j] += tmp;
    }
  }
  return ans;
}