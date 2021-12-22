#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
int dp[6][N];
/*
possible suffixes
0: { 0 1 }
1: { -1 0 }
2: { 0 1 2 }
3: { -2 -1 0 }
4: { -1 0 1 }
5: { 0 }
*/
/*
btw:
dp[0,1][i] = (i >= 1)
dp[2,3][i] = 2 ** ((i-1) / 2) - 1
dp[4][i] = 2 ** ((i+1) / 2) - 2
dp[5][i] = (i == 0)
*/
int tr[6][2] {
  {2, 1},
  {0, 3},
  {-1,4},
  {4,-1},
  {2, 3},
  {0, 1}
};

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n; cin >> n;
  int m; cin >> m;
  string s; cin >> s;
  dp[5][0] = 1;
  for (int i = 1; i <= n; ++i) {
    dp[0][i] = (dp[1][i-1] + dp[5][i-1]) % m;
    dp[1][i] = (dp[0][i-1] + dp[5][i-1]) % m;
    dp[2][i] = (dp[0][i-1] + dp[4][i-1]) % m;
    dp[3][i] = (dp[1][i-1] + dp[4][i-1]) % m;
    dp[4][i] = (dp[2][i-1] + dp[3][i-1]) % m;
  }

  int ans = 1;
  int t = 5;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'P' && t != 2) {
      int to = tr[t][0];
      if (i == n - 1) ans = (ans + 1) % m;
      if (to == 0) ans = (ans + dp[0][n-i-1] + dp[1][n-i-1] + dp[3][n-i-1] + dp[4][n-i-1]) % m;
      if (to == 2) ans = (ans + dp[1][n-i-1] + dp[3][n-i-1]) % m;
      if (to == 4) ans = (ans + dp[0][n-i-1] + dp[1][n-i-1] + dp[4][n-i-1]) % m;
    }
    t = tr[t][s[i] == 'P'];
  }
  cout << ans << "\n";
}
