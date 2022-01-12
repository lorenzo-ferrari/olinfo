#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n; cin >> n;
  int m; cin >> m;
  vector<vector<LL>> o(n, vector<LL>(m));
  vector<vector<LL>> p(n, vector<LL>(m));
  vector<vector<LL>> de(n, vector<LL>(m));
  vector<vector<LL>> dw(n, vector<LL>(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    cin >> o[i][j];
    p[i][j] = de[i][j] = dw[i][j] = o[i][j];
  }
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (i-1 >= 0 && j+1 < m) {
      p[i][j] += p[i-1][j+1];
      de[i][j] += de[i-1][j+1];
    }
  }
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (i-1 >= 0 && j-1 >= 0) {
      p[i][j] += p[i-1][j-1];
      dw[i][j] += dw[i-1][j-1];
    } else if (i-2 >= 0 && j == 0) {
      p[i][j] += p[i-2][j];
    }
  }
  for (int i = n-1; i > 0; --i) for (int j = 0; j < m; ++j) {
    p[i][j] += p[i-1][j];
  }
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < m; ++j) {
  //     cout << setw(4) << p[i][j];
  //   }
  //   cout << endl;
  // }
  // return 0;
  auto prf = [&](int x, int y) -> LL {
    while (y < 0) --x, ++y;
    while (y >= m) --x, --y;
    if (x < 0) return 0LL;
    return p[x][y];
  };
  auto eval = [&](int x, int y, int r) -> LL {
    if (r == 1) return o[x][y];
    LL ans = 0;
    ans += prf(x+(r-1),y);
    ans -= prf(x-1,y+(r-1));
    ans -= prf(x-1,y-(r-1));
    ans += prf(x-r,y);
    if (x && y + r < m) ans -= de[x-1][y+r];
    if (x && y - r >=0) ans -= dw[x-1][y-r];
    return ans;
  };
  array<int, 2> best{0,0};
  LL bestval = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    int r = 1e9;
    r = min(r, i+1);
    r = min(r, j+1);
    r = min(r, n-i);
    r = min(r, m-j);
    if (eval(i,j,r) > bestval) {
      bestval = eval(i,j,r);
      best = {i, j};
    }
  }
  cout << best[0] << " " << best[1] << "\n";
}
