#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

#define MAX 5005

int N, K;
int v[MAX];
int dp[MAX][MAX];

int solve(int n, int k)
{
  if(k <= 0 || n == 0)
    return 0;
  if (dp[n][k] != 0)
    return dp[n][k];

  int nonMangio = solve(n-1, k); // non mangio piatto n
  int mangio = v[n] + solve(n-1, k-v[n]); // mangio piatto n

  if(nonMangio >= k && nonMangio < mangio)
    return dp[n][k] = nonMangio;
  return dp[n][k] = mangio;
}

int main()
{
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  cin >> N >> K;
  for(int i = 1; i <= N; ++i)
    cin >> v[i];
  cout << solve(N, K);
}
