#include <bits/stdc++.h>
using namespace std;

int solve(int n, int* s) {
  vector<int> md(n+1, 1);
  for (int i = 2; i <= n; ++i)
    if (md[i] == 1)
      for (int j = i; j <= n; j += i)
        if (md[j] == 1)
          md[j] = i;
  vector<int> div;
  for (int i = 1; i <= n; ++i)
    if (n % i == 0)
      div.push_back(i);
  vector<vector<bool>> flag(div.size());
  for (int i = 0; i < div.size(); ++i)
    flag[i].assign(div[i], true);
  int ans = 0;
  for (int i = div.size() - 2; i >= 0; --i) {
    int p = div[i] * md[n / div[i]];
    int idx = lower_bound(div.begin(), div.end(), p) - div.begin();
    for (int j = 0; j < div[i]; ++j) {
      for (int k = 0; k * div[i] < p && flag[i][j]; ++k) {
        flag[i][j] = flag[idx][j + k*div[i]] && s[j] == s[j + k*div[i]];
      }
      ans += flag[i][j];
    }
  }
  return ans;
}
