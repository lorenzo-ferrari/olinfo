#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  int k; cin >> k;
  vector<vector<array<int, 2>>> s(n, vector<array<int, 2>>(k));
  for (int i = 0; i < n; ++i) for (int j = 0; j < k; ++j) {
    cin >> s[i][j][0] >> s[i][j][1];
  }
  vector<double> dp(n+1, 0); dp[n] = 1.0;
  vector<double> gain(k, 0); // gain[i] = max gain if I own 1 stock i
  for (int i = n-1; i >= 0; --i) {
    dp[i] = dp[i + 1];
    for (int j = 0; j < k; ++j) {
      gain[j] = max(gain[j], s[i][j][1] * dp[i]);
      dp[i] = max(dp[i], gain[j] / s[i][j][0]);
    }
    for (int j = 0; j < k; ++j) {
      gain[j] = max(gain[j], s[i][j][1] * dp[i]);
      dp[i] = max(dp[i], gain[j] / s[i][j][0]);
    }
  }
  cout << fixed << setprecision(9) << dp[0] << "\n";
}
