#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int mod = 10007;

int fact(int n) {
  return n <= 1 ? 1 : n * fact(n-1) % mod;
}

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int l; cin >> l;
  int n; cin >> n;
  int k; cin >> k;
  // count how many ways to choose a subset of k elements with sum >= l
  vector<int> v(n-1);
  for (int& i : v) cin >> i;
  vector<vector<int>> dp(k+1, vector<int>(l+1));
  // dp[i][j] = # ways of take i and remove j liters
  dp[0][0] = 1;
  for (int i = 0; i < n-1; ++i) {
    auto prv = dp;
    for (int j = 0; j <= k; ++j) {
      for (int jj = 0; jj <= l; ++jj) {
        dp[j][jj] = prv[j][jj];
        if (j != 0 && jj >= v[i]) dp[j][jj] = (dp[j][jj] + prv[j-1][jj - v[i]]) % mod;
      }
    }
  }
  int bad = 0;
  for (int i = 0; i < l; ++i) bad += dp[k][i];
  bad = (bad % mod) * fact(k) % mod * fact(n-1-k) % mod;
  int goods = (fact(n-1) - bad + mod) % mod;
  cout << goods << "\n";
}
