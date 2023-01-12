#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

static int16_t getint() {
  int16_t n = 0;
  char c = getchar_unlocked();
  while ('0' <= c && c <= '9') {
    n = 10 * n + c - '0';
    c = getchar_unlocked();
  }
  return n;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int16_t n = getint();
  int16_t m = getint();
  int16_t schifo2 = 0;
  vector<vector<int16_t>> mask(n, vector<int16_t>(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    mask[i][j] = getint();
    schifo2 |= mask[i][j];
  }
  if (!schifo2) {
    cout << max(n, m) << "\n";
    return 0;
  }
  vector<vector<vector<array<int16_t, 3>>>> g(2*n, vector<vector<array<int16_t, 3>>>(2*m));
  for (int i = 0; i < 2*n; ++i) for (int j = 0; j < 2*m; ++j) {
    int16_t cmask = mask[i/2][j/2];
    if (!(i & 1) && !(j & 1)) {
      g[i][j].push_back({i-1, j, 1});
      g[i][j].push_back({i, j-1, 1});
      g[i][j].push_back({i-1, j-1, 1});
      if (!(cmask & 1)) g[i][j].push_back({i, j+1, 0});
      if (!(cmask & 8)) g[i][j].push_back({i+1, j, 0});
    } else if (!(i & 1) && (j & 1)) {
      g[i][j].push_back({i-1, j, 1});
      g[i][j].push_back({i, j+1, 1});
      g[i][j].push_back({i-1, j+1, 1});
      if (!(cmask & 1)) g[i][j].push_back({i, j-1, 0});
      if (!(cmask & 2)) g[i][j].push_back({i+1, j, 0});
    } else if ((i & 1) && !(j & 1)) {
      g[i][j].push_back({i+1, j, 1});
      g[i][j].push_back({i, j-1, 1});
      g[i][j].push_back({i+1, j-1, 1});
      if (!(cmask & 4)) g[i][j].push_back({i, j+1, 0});
      if (!(cmask & 8)) g[i][j].push_back({i-1, j, 0});
    } else if ((i & 1) && (j & 1)) {
      g[i][j].push_back({i+1, j, 1});
      g[i][j].push_back({i, j+1, 1});
      g[i][j].push_back({i+1, j+1, 1});
      if (!(cmask & 2)) g[i][j].push_back({i-1, j, 0});
      if (!(cmask & 4)) g[i][j].push_back({i, j-1, 0});
    } else {
      assert(false);
    }
  }
  vector<vector<int>> d(2*n, vector<int>(2*m, 1e9));
  priority_queue<array<int, 3>> Q;
  d[0][0] = 1;
  Q.push({-1, 0, 0});
  while (!Q.empty()) {
    auto [t, x, y] = Q.top();
    Q.pop();
    if (x == 2*n-1 && y == 2*m-1) break;
    if (-t > d[x][y]) continue;
    for (auto [i, j, w] : g[x][y]) {
      if (i < 0 || j < 0 || i >= 2*n || j >= 2*m) continue;
      if (d[i][j] > d[x][y] + w) {
        d[i][j] = d[x][y] + w;
        Q.push({-d[i][j], i, j});
      }
    }
  }
  cout << (d[2*n-1][2*m-1] == 1e9 ? -1 : d[2*n-1][2*m-1]) << "\n";
}
