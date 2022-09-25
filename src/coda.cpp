#include <bits/stdc++.h>
using namespace std;

vector<int> cucina(int n, int k, int x, vector<int> h) {
  vector<int> f(x);
  for (int i = 0; i < n; ++i) {
    ++f[h[i]];
  }
  // dp[i] = risposta per [i,x]
  // c[i] = massimo storico della coda che lascio a i-1
  vector<int> dp(x + 1);
  vector<int> c(x + 1);
  c[x] = k - 1;
  for (int i = x - 1; i >= 0; --i) {
    int nw = min(f[i], k - c[i + 1]);
    c[i] = max(0, c[i + 1] + nw - 1);
    dp[i] = dp[i + 1] + nw;
  }
  dp.pop_back();
  return dp;
}
