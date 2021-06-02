#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int64_t n, d, ans = 0;
  cin >> n >> d;

  deque <int> Q;
  for (int i = 0, p; i < n; ++i) {
    cin >> p;
    while (!Q.empty() && Q.back() <= p - d)
      Q.pop_back();
    ans += Q.size();
    Q.push_front(p);
  }

  cout << ans << "\n";
}