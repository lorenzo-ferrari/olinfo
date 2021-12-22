#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int64_t n, m;
  cin >> n >> m;

  if (n == 1) {
    cout << 1000000 << "\n";
    return 0;
  }

  vector<vector<double>> av(m, vector<double> (n));
  for (int64_t i = 0; i < m; i++) {
    double tot = 0;
    for (int64_t j = 0, w; j < n; j++) {
      cin >> w;
      av[i][j] = w * 1000000;
      tot += w;
    }

    for (int64_t j = 0; j < n; j++)
      av[i][j] /= tot;
  }

  vector<double> ans(n);
  for (int64_t i = 0; i < n; i++) {
    for (int64_t j = 0; j < m; j++) {
      ans[i] += av[j][i];
    }
    ans[i] /= m;
  }

  for (double a : ans) {
    cout << int64_t(a) << " ";
  }
  cout << "\n";
}
