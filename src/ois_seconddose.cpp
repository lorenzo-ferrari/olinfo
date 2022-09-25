#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  map<int, bool> mp;
  for (int i = 0; i < n; i++) {
    int a; cin >> a; mp[a] = true;
  }

  int ans = 0;
  for (int i = 0; i < m; i++) {
    int b; cin >> b; ans += mp[b];
  }

  cout << ans << "\n";
}
