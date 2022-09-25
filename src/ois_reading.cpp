#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  int l; cin >> l;
  vector<array<int, 2>> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i][0] >> v[i][1];
    if (v[i][1] == -1) v[i][1] = l-1;
  }
  set<int> days;
  for (int i = 0; i < l; ++i) days.insert(-i);
  sort(v.begin(), v.end(), greater<array<int, 2>>());
  int ans = 0;
  for (auto [p, d] : v) {
    auto it = days.lower_bound(-d);
    if (it != days.end()) {
      ans += p;
      days.erase(it);
    }
  }
  cout << ans << "\n";
}
