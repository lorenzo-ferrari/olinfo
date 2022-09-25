#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int64_t n, m, c0;
vector<int64_t> p;
vector<vector<pair<int64_t, int64_t>>> g;

vector<int64_t> ord;
vector<bool> vis;
void dfs(int64_t v) {
  vis[v] = true;
  for (auto [u, w] : g[v])
    if (!vis[u])
      dfs(u);
  ord.push_back(v);
}

const int64_t INF = 1e10;
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m >> c0;

  p.resize(n);
  g.resize(n);
  vis.resize(n);

  for (int64_t &i : p)
    cin >> i;

  for (int64_t i = 0, a, b, c; i < m; i++) {
    cin >> a >> b >> c;
    g[a].push_back({b, c});
  }

  dfs(0);
  reverse(ord.begin(), ord.end());
  
  vector<vector<int64_t>> dp(n, vector<int64_t> (201, INF));
  
  for (int64_t i = c0; i >= 0; i--) {
    dp[0][i] = p[0] >> (c0 - i);
  }

  for (int64_t v : ord) {
    for (auto [u, cn] : g[v]) {
      for (int64_t i = 0; i <= 100 && dp[v][i] != INF; i++) {
        for (int64_t j = i + cn; j >= 0; j--)
          dp[u][j] = min(dp[u][j], max(dp[v][i], p[u] >> (i + cn - j)));
      }
    }
  }
  
  cout << dp[n - 1][0] << "\n";
}
