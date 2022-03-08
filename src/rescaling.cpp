#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> dp(n); dp[0] = 1;
  for (int i = 1; i < n; ++i) {
    int mx = 0;
    for (int j = 0; j < i; ++j) {
      if (a[i] < a[j] || a[i] % a[j] == 0) {
        mx = max(mx, dp[j]);
      }
    }
    dp[i] = mx + 1;
  }
  cout << n - *max_element(dp.begin(), dp.end()) << "\n";
}
