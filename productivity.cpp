#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
  int n, m, e;
  cin >> n >> m >> e;

  int ans = 0;
  while (m <= n)
    ans = max(ans, e % (m++));

  cout << ans << "\n";
}
