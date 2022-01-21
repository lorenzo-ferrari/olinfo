#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const LL mod = 1e9 + 7;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s; cin >> s;
  reverse(s.begin(), s.end());
  LL ans = 0;
  for (LL i = 0, p = 1; i < int(s.size()); ++i) {
    ans = (ans + p * (s[i] - 'a' + 1)) % mod;
    p = p * 26 % mod;
  }
  ans = (ans - 1 + mod) % mod;
  cout << ans << "\n";
}
