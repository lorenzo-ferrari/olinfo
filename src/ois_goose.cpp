#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  vector<int> v(n);
  for (int& i : v) cin >> i;
  for (int roll = 1; roll <= 6; ++roll) {
    int pos = 0;
    int ans = 0;
    for (; pos < n;) {
      pos += roll;
      ++ans;
      while (pos < n && v[pos]) {
        pos += v[pos];
      }
    }
    cout << ans << " ";
  }
  cout << "\n";
}
