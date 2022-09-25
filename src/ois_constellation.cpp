#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  vector<pair<int, int>> v(n);
  map<int, int> mx;
  map<int, int> my;
  for (auto& [x, y] : v) {
    cin >> x >> y;
    ++mx[x], ++my[y];
  }
  LL ans = 0;
  for (auto [x, y] : v) {
    ans += (LL)(mx[x]-1)*(my[y]-1);
  }
  cout << ans << "\n";
}
