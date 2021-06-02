#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int main() {
#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  int n;
  cin >> n;

  vector<vector<bool>> g(n + 1, vector<bool> (n + 1));

  for (int i = 0, a, b; i < n * (n - 1) / 2; ++i) {
    cin >> a >> b;
    g[a][b] = true;
  }

  vector<int> path(3);
  if (g[1][2] && g[2][3]) { path[0] = 1; path[1] = 2; path[2] = 3; }
  if (g[1][3] && g[3][2]) { path[0] = 1; path[1] = 3; path[2] = 2; }
  if (g[2][1] && g[1][3]) { path[0] = 2; path[1] = 1; path[2] = 3; }
  if (g[2][3] && g[3][1]) { path[0] = 2; path[1] = 3; path[2] = 1; }
  if (g[3][1] && g[1][2]) { path[0] = 3; path[1] = 1; path[2] = 2; }
  if (g[3][2] && g[2][1]) { path[0] = 3; path[1] = 2; path[2] = 1; }

  for (int v = 4; v <= n; ++v) {
    if (g[v][path[0]]) { path.insert(path.begin(), v); }
    else if (g[path.back()][v]) { path.insert(path.end(), v); }
    else {
      for (int i = 1; i < path.size(); i++) {
        if (g[path[i - 1]][v] && g[v][path[i]]) {
          path.insert(path.begin() + i, v);
          break;
        }
      }
    }
  }

  cout << n - 1 << "\n";
  for (int i = 1; i < n; ++i) {
    cout << path[i - 1] << " " << path[i] << "\n";
  }
}