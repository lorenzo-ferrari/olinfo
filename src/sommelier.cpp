#include <bits/stdc++.h>
using namespace std;

const int N = 100;

int n;
int v[N];
int dp[N][N];

int solve(int i, int mn) {
  if (i >= n)
    return 0;
  if (dp[i][mn] != 0)
    return dp[i][mn];
  int ans = solve(i+1, mn); // non bere il vino i
  if (v[i] >= mn)
    ans = max(ans, solve(i+2, v[i]) + 1); // bevi il vino i

  return dp[i][mn] = ans;
}

int main() {
#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  cout << solve(0,0) << "\n";
}
