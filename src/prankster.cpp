#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
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
