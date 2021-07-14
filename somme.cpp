#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  int n;
  cin >> n;
  vector<int> v(n);
  vector<int> p(n+1);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    p[i+1] = p[i] + v[i];
  }
  vector<vector<int>> dp(n+1, vector<int> (n+1));
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < n+1-i; j++) {
      dp[j][j+i] = 1e9;
      for (int k = 1; k < i; k++) {
        dp[j][j+i] = min(dp[j][j+i], max(dp[j][j+k], dp[j+k][j+i]));
      }
      dp[j][j+i] = max(dp[j][j+i], abs(p[j+i]-p[j]));
    }
  }

  cout << dp[0][n] << endl;
}