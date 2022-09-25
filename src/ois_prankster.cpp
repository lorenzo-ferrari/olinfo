#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

  int n; cin >> n;
  vector<int> a(n + 2);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  int x = 0;
  int y = 0;
  for (int i = 1; i < n+2; ++i) {
    x += ((a[i] - a[i-1] + 3) % 3 == 1);
    y += ((a[i] - a[i-1] + 3) % 3 == 2);
  }
  if (x < y) swap(x, y);
  int ans = (x - y) - (x - y) / 3 + y;
  cout << ans << "\n";
}
