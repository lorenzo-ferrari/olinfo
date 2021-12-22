#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pair<int, int>> v(2*n);
  for (int i = 0, a, b; i < n; i++) {
    cin >> a >> b;
    v[i << 1] = {a, 1};
    v[i << 1 | 1] = {b, 0};
  }
  sort(v.begin(), v.end());
  long long ans = 0, buffer = 1;
  for (auto &[a, b] : v) {
     if (b) {
        ans += buffer++;
     } else {
        ans += --buffer;
     }
  }
  cout << ans << "\n";
}
