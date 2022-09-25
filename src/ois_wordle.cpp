#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    char c; cin >> c;
    cnt += (c == '_');
  }
  LL ans = 1;
  for (int i = 0, mul = 26-n+1; i < cnt ; ++i, ++mul) {
    ans *= mul;
  }
  cout << ans << "\n";
}
