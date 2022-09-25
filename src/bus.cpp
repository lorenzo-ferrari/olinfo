#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int pianifica(int n, int l, vector<vector<int>> f) {
  vector<vector<int>> linee(n);
  for (int i = 0; i < l; ++i) {
    for (int j : f[i]) {
      linee[j].push_back(i);
    }
  }
  for (int i = 0; i < n; ++i) {
    linee[i].push_back(l);  // linea diversa da tutte, x cambio
  }
  vector<vector<vector<array<int, 3>>>> adj(n);
  for (int i = 0; i < n; ++i) {
    adj[i].resize(linee[i].size());
  }
  vector<int> cnt(n, 0);  // conta quante linee ha gia' i
  for (int i = 0; i < l; ++i) {
    for (int j = 0; j + 1 < (int)f[i].size(); ++j) {
      int cur = f[i][j];
      int nxt = f[i][j + 1];
      adj[cur][cnt[cur]].push_back({nxt, cnt[nxt], 0});
      adj[cur][cnt[cur]].push_back({cur, (int)linee[cur].size() - 1, 0});
      adj[cur][linee[cur].size() - 1].push_back({cur, cnt[cur], 1});
      ++cnt[cur];
    }
    int cur = f[i].back();
    adj[cur][cnt[cur]].push_back({cur, (int)linee[cur].size() - 1, 0});
    adj[cur][linee[cur].size() - 1].push_back({cur, cnt[cur], 1});
    ++cnt[cur];
  }
  vector<vector<int>> d(n);
  for (int i = 0; i < n; ++i) {
    d[i].assign(linee[i].size(), 1e9);
  }

  vector<vector<array<int, 2>>> Q(n+1);
  for (int i = 0; i < (int)linee[0].size(); ++i) {
    d[0][i] = 0;
    Q[0].push_back({0, i});
  }
  for (int td = 0; td <= n; ++td) {
    while (!Q[td].empty()) {
      int tc = Q[td].back()[0];
      int tl = Q[td].back()[1];
      Q[td].pop_back();
      for (auto [u, lu, w] : adj[tc][tl]) {
        if (d[u][lu] > td + w) {
          d[u][lu] = td + w;
          Q[d[u][lu]].push_back({u, lu});
        }
      }
    }
    if (d[n-1].back() != 1e9) {
      break;
    }
  }
  int ans = d[n - 1].back();
  return ans == 1e9 ? -1 : ans;
}
