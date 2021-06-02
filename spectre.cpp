#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  int ans = 0;

  cin >> n;

  char x;
  string a, b, c;
  set<string> s;
  for (int  i = 0; i < n; i++) {
    cin >> a >> x >> b >> x >> c;
    ans += (s.find(b) == s.end() && s.find(c) == s.end());
    s.insert(a);
  }

  cout << ans << endl;
}