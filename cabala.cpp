#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define int int64_t

vector<pair<int, int>> c;

inline void gen(int n, int step) {
  if (step > 18) return;

  if (n) c.push_back({n, step});
  if (n % 10 != 3) gen(n * 10 + 3, step + 1);
  if (n % 10 != 6) gen(n * 10 + 6, step + 1);
  if (n % 10 != 9) gen(n * 10 + 9, step + 1);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  gen(0, 0);

  int t;
  cin >> t;

  while (t--) {
    int n, m, ans = 0;
    cin >> n >> m;
    for (auto [a, b] : c)
      if (b <= n && a % m > ans)
        ans = a % m;
    cout << ans << " ";
  }

  cout << "\n";
}
