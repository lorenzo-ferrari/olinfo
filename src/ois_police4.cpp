#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  LL n; cin >> n;
  LL r; cin >> r;
  LL t; cin >> t;
  LL l; cin >> l;
  vector<LL> x(n+1);
  for (int i = 1; i <= n; ++i) {
    cin >> x[i];
  }
  x.push_back(l);
  LL mod = 2*t;
  vector<vector<LL>> dp(n+2, vector<LL> (r+1, 1e15));
  for (int j = 0; j <= r; ++j) dp[0][j] = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= r; ++j) {
      if (dp[i][j] % mod >= t) {
        dp[i+1][j] = min(dp[i+1][j], dp[i][j] + mod-(dp[i][j]%mod) + x[i+1] - x[i]);
        if (j != r) dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + x[i+1] - x[i]);
      } else {
        dp[i+1][j] = min(dp[i+1][j], dp[i][j] + x[i+1] - x[i]);
      }
    }
  }
  LL ans = 1e15;
  for (int j = 0; j <= r; ++j) {
    ans = min(ans, dp[n+1][j]);
  }
  cout << ans << "\n";
}