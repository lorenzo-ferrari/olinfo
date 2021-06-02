#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");

  int n;
  int m;
  cin >> n;
  cin >> m;

  int xmx = -90;
  int ymx = -90;
  int xmn = 1e9;
  int ymn = 1e9;
  vector<pair<int, int>> s(m);
  for (auto &[si, sj] : s) {
    cin >> si >> sj;
    xmx = max(xmx, si);
    ymx = max(ymx, sj);
    xmn = min(xmn, si);
    ymn = min(ymn, sj);
  }

  vector<vector<int>> g(n, vector<int> (n));
  for (auto &x : g)
    for (auto &y : x)
      cin >> y;

  int sx;
  int sy;
  int c = 1e9;
  for (int shx = -xmn; shx < n - xmx; ++shx) {
    for (int shy = -ymn; shy < n - ymx; ++shy) {
      int tc = 0;
      for (auto &[si, sj] : s) {
        tc += g[si + shx][sj + shy];
      }
      if (tc < c) {
        c = tc;
        sx = shx;
        sy = shy;
      }
    }
  }

  cout << sx << " ";
  cout << sy << " ";
  cout << c  << "\n";
}