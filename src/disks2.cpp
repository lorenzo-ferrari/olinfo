#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  int t; cin >> t;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i];
  }
  for (int i = 1; i < n; ++i) {
    if (a[i] + 24 - b[i - 1] >= t) {
      cout << i - 1 << "\n";
      return 0;
    }
  }
  cout << -1 << "\n";
}
