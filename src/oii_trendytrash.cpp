/**
* user:  ferrari
* fname: Lorenzo
* lname: Ferrari
* task:  trendytrash
* score: 100.0
* date:  2021-11-16 14:49:05.931399
*/
#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
using LL = long long;

int pulisci(int n, int m, vector<string> s) {
  vector<array<int, 2>> a(m);
  vector<array<int, 2>> l(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ++a[j][s[i][j]-'0'];
      ++l[i][s[i][j]-'0'];
    }
  }
  vector<vector<bool>> b(n, vector<bool>(m, true));
  queue<pair<int, int>> Q; // {idx, a / l};
  for (int i = 0; i < m; ++i) if (!a[i][0] || !a[i][1]) Q.push({i, 0});
  for (int i = 0; i < n; ++i) if (!l[i][0] || !l[i][1]) Q.push({i, 1});
  while (!Q.empty()) {
    auto [idx, t] = Q.front();
    Q.pop();
    if (t == 0) {
      for (int i = 0; i < n; ++i) {
        if (b[i][idx]) {
          b[i][idx] = false;
          --l[i][s[i][idx]-'0'];
          if (l[i][s[i][idx]-'0'] == 0)
            Q.push({i, 1});
        }
      }
    } else if (t == 1) {
      for (int i = 0; i < m; ++i) {
        if (b[idx][i]) {
          b[idx][i] = false;
          --a[i][s[idx][i]-'0'];
          if (a[i][s[idx][i]-'0'] == 0)
            Q.push({i, 0});
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      ans += b[i][j];
  return ans;
}
