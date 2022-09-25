#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n; cin >> n;
  vector<array<int, 2>> v;
  for (int i = 0, a, b; i < n; ++i) {
    cin >> a >> b;
    v.push_back({a, 1});
    v.push_back({b, -1});
  }
  sort(v.begin(), v.end());
  int cur = 0;
  long long ans = 0;
  for (auto& [_, d] : v) {
    if (d == 1) {
      ans += ++cur;
    } else {
      --cur;
    }
  }
  cout << ans << "\n";
}
