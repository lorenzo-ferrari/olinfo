#include <bits/stdc++.h>
using namespace std;

#define N 1000

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n; cin >> n;
  int m; cin >> m;
  vector<int> k(n);
  for (int i = 0; i < n; ++i) {
    cin >> k[i];
  }
  auto range_cost = [&](int i, int j) {
    // return cost of fixing positions [i, j]
    int l = (i == 0 ? 0 : k[i-1] + 1);
    int r = (j == n - 1 ? m-1 : k[j+1] - 1);
    return l == r ? 0 : r-l+1;
  };
  int* dp[N];
  vector<int16_t> id(n), prv(n);
  for (int i = 0; i < n; ++i) {
    dp[i] = (int*)malloc((n - i) * sizeof(int));
  }
  for (int i = 0; i < n; ++i) {
    dp[i][i-i] = range_cost(i, i);
    prv[i] = i;
  }
  for (int16_t sz = 2; sz <= n; ++sz) {
    for (int16_t i = 0; i <= n - sz; ++i) {
      dp[i][(i+sz-1)-i] = INT_MAX;
      id[i] = -1;
      int base = range_cost(i, (i+sz-1));
      for (int16_t mid = prv[i]; mid <= prv[i+1]; ++mid) {
        int cost_low = (mid == i ? 0 : dp[i][mid - 1 - i]);
        int cost_high = (mid == (i+sz-1) ? 0 : dp[mid + 1][(i+sz-1) - mid - 1]);
        int cost = base + cost_low + cost_high;
        if (cost < dp[i][(i+sz-1)-i]) {
          dp[i][(i+sz-1)-i] = cost;
          id[i] = mid;
        }
      }
    }
    prv = id;
  }
  cout << dp[0][n-1] << "\n";
}
