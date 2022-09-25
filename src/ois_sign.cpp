#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int64_t t, a, b;
  cin >> t;
  while (t--) {
    cin >> a >> b;
    if (a > b)
      swap(a, b);
    if (a > 0)
      cout << '+' << "\n";
    else if (b >= 0)
      cout << '0' << "\n";
    else if ((b - a + 1) % 2 == 0)
      cout << '+' << "\n";
    else
      cout << '-' << "\n";
  }
}
