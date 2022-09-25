#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
using ll = int64_t;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  ll n, m, s, e;
  cin >> n >> m >> s >> e;
  vector<vector<pair<int, int>>> g(n + 1);
  for (int i = 0, a, b, c; i < m; ++i) {
    cin >> a >> b >> c;
    g[a].push_back({b, c});
  }
  vector<ll> d(n + 1, 1LL << 42);
  priority_queue<pair<ll, ll>> Q;
  Q.push({0, s}); d[s] = 0;
  while (!Q.empty()) {
    ll p = -Q.top().first;
    ll v =  Q.top().second;
    Q.pop();
    if (p > d[v])
      continue;
    for (auto [u, w] : g[v]) {
      if (d[u] > w + p) {
        d[u] = w + p;
        Q.push({-d[u], u});
      }
    }
  }
  cout << d[e] << "\n";
}
