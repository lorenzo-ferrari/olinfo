#include <bits/stdc++.h>
using namespace std;

int dx[] {0,  0,  1,  1,  1, -1, -1, -1};
int dy[] {1, -1,  0,  1, -1,  0,  1, -1};

int main() {
  int n; cin >> n;
  int m; cin >> m;
  vector<vector<int>> g(n, vector<int>(m));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    char c; cin >> c;
    g[i][j] = c - '0';
  }
  vector<int> frq(10000);
  auto conc = [](int a, int b, int c, int d) -> int {
    return 1000*a + 100*b + 10*c + d;
  };
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (g[i][j] == 0) continue;
    for (int k = 0; k < 8; ++k) {
      int li = i + 3*dx[k];
      int lj = j + 3*dy[k];
      if (0 <= li && li <= n-1 && 0 <= lj && lj <= m-1) {
        ++frq[conc(g[i][j],
                   g[i+1*dx[k]][j+1*dy[k]],
                   g[i+2*dx[k]][j+2*dy[k]],
                   g[i+3*dx[k]][j+3*dy[k]])];
      }
    }
  }
  int best = 1;
  for (int i = 2; i <= 9999; ++i) {
    if (frq[i] > frq[best]) {
      best = i;
    }
  }
  cout << best << " " << frq[best] << "\n";
}
