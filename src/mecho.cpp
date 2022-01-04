#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int32_t main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n, s;
  cin >> n >> s;
  vector<vector<char>> m(n, vector<char> (n));
  int xs, ys;
  int xe, ye;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    cin >> m[i][j];
    if (m[i][j] == 'M') xs = i, ys = j;
    if (m[i][j] == 'D') xe = i, ye = j;
  }
  queue<pair<int, int>> Q;
  vector<vector<int>> d(n, vector<int> (n, 1e9));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (m[i][j] == 'H') {
      d[i][j] = 0;
      Q.push({i, j});
    }
  }
  while (!Q.empty()) {
    auto [x, y] = Q.front();
    Q.pop();
    if (x     && (m[x-1][y  ] == 'G' || m[x-1][y  ] == 'M') && d[x-1][y  ] > d[x][y] + 1) d[x-1][y  ] = d[x][y] + 1, Q.push({x-1, y  });
    if (y     && (m[x  ][y-1] == 'G' || m[x  ][y-1] == 'M') && d[x  ][y-1] > d[x][y] + 1) d[x  ][y-1] = d[x][y] + 1, Q.push({x  , y-1});
    if (x<n-1 && (m[x+1][y  ] == 'G' || m[x+1][y  ] == 'M') && d[x+1][y  ] > d[x][y] + 1) d[x+1][y  ] = d[x][y] + 1, Q.push({x+1, y  });
    if (y<n-1 && (m[x  ][y+1] == 'G' || m[x  ][y+1] == 'M') && d[x  ][y+1] > d[x][y] + 1) d[x  ][y+1] = d[x][y] + 1, Q.push({x  , y+1});
  }
  auto psb = [&](int delay) {
    // bfs from mecho's location
    // it's possible iff dist_from_mecho[i][j]/s + delay < d[i][j]
    queue<pair<int, int>> Q;
    vector<vector<int>> dm(n, vector<int> (n, 1e9));
    Q.push({xs, ys});
    dm[xs][ys] = 0;
    while (!Q.empty()) {
      auto [x, y] = Q.front();
      Q.pop();
      if (delay + (dm[x][y]) / s >= d[x][y]) continue;
      if (x     && m[x-1][y  ] != 'T' && dm[x-1][y  ] > dm[x][y] + 1 && delay + (dm[x][y] + 1) / s < d[x-1][y  ]) dm[x-1][y  ] = dm[x][y] + 1, Q.push({x-1, y  });
      if (y     && m[x  ][y-1] != 'T' && dm[x  ][y-1] > dm[x][y] + 1 && delay + (dm[x][y] + 1) / s < d[x  ][y-1]) dm[x  ][y-1] = dm[x][y] + 1, Q.push({x  , y-1});
      if (x<n-1 && m[x+1][y  ] != 'T' && dm[x+1][y  ] > dm[x][y] + 1 && delay + (dm[x][y] + 1) / s < d[x+1][y  ]) dm[x+1][y  ] = dm[x][y] + 1, Q.push({x+1, y  });
      if (y<n-1 && m[x  ][y+1] != 'T' && dm[x  ][y+1] > dm[x][y] + 1 && delay + (dm[x][y] + 1) / s < d[x  ][y+1]) dm[x  ][y+1] = dm[x][y] + 1, Q.push({x  , y+1});
    }
    return dm[xe][ye] != 1e9;
  };
  int l = 0, r = n * n + 2;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (psb(mid))
      l = mid;
    else
      r = mid;
  }
  cout << (psb(l) ? l : -1) << "\n";
}
