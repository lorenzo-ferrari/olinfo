#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int monete(int n, int v[]) {
  vector<unordered_map<int, int>> m(n+1);

  for (int i = 2; i <= n; ++i)
    for (int j = i; j <= n; j += i)
      m[i][v[j-1]] += 1;

  int ans = 0;
  for (auto &x : m)
    for (auto &y : x)
      ans = max(ans, y.second);

  return ans;
}