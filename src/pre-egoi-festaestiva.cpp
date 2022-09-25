#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int organizza(int n, int x, int y, vector<int> a, vector<int> b) {
  vector<int> z{x, y};
  for (int i : a) { z.push_back(i); }
  for (int i : b) { z.push_back(i); z.push_back(i+1); }
  sort(z.begin(), z.end());
  z.resize(unique(z.begin(), z.end()) - z.begin());
  x = lower_bound(z.begin(), z.end(), x) - z.begin();
  y = lower_bound(z.begin(), z.end(), y) - z.begin();
  for (int& i : a) i = lower_bound(z.begin(), z.end(), i) - z.begin();
  for (int& i : b) i = lower_bound(z.begin(), z.end(), i) - z.begin();
  int nn = z.size();
  vector<int> p(nn + 1);
  for (int i = 0; i < n; ++i) {
    ++p[a[i]];
    --p[b[i]+1];
  }
  for (int i = 0; i < nn; ++i) {
    p[i+1] += p[i];
  }
  int ans = 0;
  for (int i = x; i <= y; ++i) {
    ans = max(ans, n - p[i]);
  }
  return ans;
}
