#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e4;

int main()
{
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int n;
  int best = 1;
  int v[MAX];
  int dp[MAX];

  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> v[i];

  for (int i = n-1; i >= 0; --i)
  {
    int massimo = 1;
    for (int j = i+1; j < n; ++j)
      if (v[j] < v[i])
        massimo = max(massimo, dp[j] + 1);
    dp[i] = massimo;
    best = max(best, massimo);
  }

  cout << best << "\n";
}
