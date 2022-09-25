#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n, m, t;
  cin >> n >> m >> t;
  vector<vector<array<int, 3>>> g(n);
  for (int i = 0, a, b, w, e; i < m; ++i) {
    cin >> a >> b >> w >> e;
    g[a].push_back({b, w, e});
  }
  vector<int> d(n, 1e9);
  d[0] = 0;
  priority_queue<pair<int, int>> Q;
  Q.push({0, 0});
  while (!Q.empty()) {
    int w = -Q.top().first;
    int v =  Q.top().second;
    Q.pop();
    if (d[v] < w)
      continue;
    for (auto [u, c, e] : g[v]) {
      int nw = w + c;
      if (nw >= d[u]) continue;
      if (e == 0 || nw <= t) {
        d[u] = nw;
        Q.push({-nw, u});
      }
    }
  }
  cout << (d[n-1] == 1e9 ? -1 : d[n-1]) << "\n";
}
