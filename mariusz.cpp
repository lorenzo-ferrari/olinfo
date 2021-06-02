#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
  int n, e;

  int64_t u[4];
  int64_t d[4];
  int64_t m[4];

  cin >> n >> e;
  for (int i = 0; i < 4; i++) cin >> u[i];
  for (int i = 0; i < 4; i++) cin >> d[i];
  for (int i = 0; i < 4; i++) cin >> m[i];

  vector<int64_t> uu(n); uu[0] = u[0];
  vector<int64_t> dd(n); dd[0] = d[0];
  vector<int64_t> mm(n); mm[0] = m[0];

  for (int i = 1; i < n; i++) {
    uu[i] = (u[1] * uu[i-1] + u[2]) % u[3];
    dd[i] = (d[1] * dd[i-1] + d[2]) % d[3];
    mm[i] = (m[1] * mm[i-1] + m[2]) % m[3];
  }

  const int INF = 1e15;
  vector<vector<int64_t>> dp (n+2, vector<int64_t> (21,INF));

  for (int i = 0; i < 21; i++) {
    dp[0][i] = 0;
    if (i > 0)
      dp[1][i-1] = min(dp[1][i-1], uu[0]);
    if (i < 20)
      dp[1][i+1] = min(dp[1][i+1], mm[0]);
  }

  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < 21; j++) {
      if (j < 20)
        dp[i][j] = min(dp[i][j], dp[i-1][j+1] + uu[i-1]);
      dp[i][j] = min(dp[i][j], dp[i-2][j] + dd[i-1]);
      if (j)
        dp[i][j] = min(dp[i][j], dp[i/2][j-1] + mm[i-1]);
    }
  }

  //cout << "u: ";for (int i = 0; i < n; i++) cout << uu[i] << " "; cout << endl;
  //cout << "d: ";for (int i = 0; i < n; i++) cout << dd[i] << " "; cout << endl;
  //cout << "m: ";for (int i = 0; i < n; i++) cout << mm[i] << " "; cout << endl;

  cout << dp[n][0] << endl;

  return 0;

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= e; j++)
      cout << dp[i][j] << " ";
    cout << endl;
  }
}