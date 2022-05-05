#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n; cin >> n;
  vector<int> v(n);
  for (int& i : v) {
    cin >> i;
  }
  vector<int> dp(n, 1);
  for (int i = n-1; i >= 0; --i) {
    for (int j = i+1; j < n; ++j) {
      if (v[i] > v[j] || v[j] % v[i] == 0) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }
  cout << n - *max_element(dp.begin(), dp.end()) << "\n";
}
