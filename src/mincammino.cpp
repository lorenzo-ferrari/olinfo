#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

void mincammino(int n, int m, vector<int> x, vector<int> y, vector<int> p, vector<int>& d) {
  vector<vector<array<int, 2>>> g(n);
  for (int i = 0; i < m; ++i) {
    g[x[i]].push_back({y[i], p[i]});
  }
  fill(d.begin(), d.end(), numeric_limits<int>::max());
  priority_queue<array<int, 2>> Q;
  d[0] = 0; Q.push({0, 0});
  while (!Q.empty()) {
    auto [_, v] = Q.top();
    Q.pop();
    if (d[v] < -_) {
      continue;
    }
    for (auto [u, w] : g[v]) {
      if (d[u] > d[v] + w) {
        d[u] = d[v] + w;
        Q.push({-d[u], u});
      }
    }
  }
}
