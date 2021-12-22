#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  vector<int> v(n);

  for (int &i : v)
    cin >> i;

  sort(v.begin(), v.end());

  int ans = 0;
  vector<int> dp(n, 1);
  for (int i = n - 1; i >= 0; i--)
    for (int j = i + 1; j < n; j++)
      if (!(v[i] % v[j]) || !(v[j] % v[i]))
        dp[i] = max(dp[i], dp[j] + 1);

	cout << *max_element(dp.begin(), dp.end()) << "\n";
}
