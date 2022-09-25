#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
  LL a, b, t;
  cin >> a >> b >> t;
  b -= a;
  a = 0;
  LL ans = ((b + t) / 24 - 1) * b;
  ans += min(b, (t + b) % 24);
  cout << ans << "\n";
}
