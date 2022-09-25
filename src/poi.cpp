#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, t, p;
  cin >> n >> t >> p;
  vector<int> pt(t, n);
  vector<int> cnt(n, 0);
  vector<vector<bool>> solved(n, vector<bool>(t));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < t; ++j) {
      int t;
      cin >> t;
      pt[j] -= (t == 1);
      solved[i][j] = t;
      cnt[i] += t;
    }
  }
  vector<int> scores(n, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < t; ++j)
      if (solved[i][j])
        scores[i] += pt[j];
  int pos = 1;
  for (int i = 0, j = p - 1; i < n; ++i) {
    if (scores[i] > scores[j] ||
        (scores[i] == scores[j] &&
         (cnt[i] > cnt[j] || (cnt[i] == cnt[j] && i < j))))
      ++pos;
  }
  cout << scores[p-1] << " " << pos << "\n";
}
