#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int main() {
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  int p;
  int ans = 1e9;
  cin >> p;
  for (int i = 1, m; i < n; i++) {
    cin >> m;
    ans = min(ans, m-p);
  }

  cout << (ans >= 0 ? ans+1 : 0) << "\n";
}