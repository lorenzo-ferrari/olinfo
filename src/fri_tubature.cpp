#include <bits/stdc++.h>
using namespace std;

int pianifica(int n, int m, int da[], int a[], int c[], int g[]) {
  vector<int> par(n, -1);
  vector<bool> matter(n);
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; ++i) {
    par[a[i]] = da[i];
    adj[da[i]].push_back(a[i]);
  }
  for (int i = 0; i < m; ++i) {
    matter[c[i]] = true;
  }
  function<int(int)> solve = [&](int v) {
    if (matter[v]) return g[v];
    int sons = 0;
    for (int u : adj[v])
      sons += solve(u);
    return min(g[v], sons);
  };
  int root = 0;
  while (par[root] != -1) root = par[root];
  return solve(root);
}
