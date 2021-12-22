#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define int int64_t

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, v;
  cin >> n >> m >> v;

  int c = (m*v*v + 1)/ 2;

  vector <int> h(n);
  for (int &i : h) cin >> i;

  vector <int> p(n+1);

  for (int i = 0; i < n-1; i++)
    p[i+1] = p[i] + 10*m*(h[i] - h[i+1]);

  vector <int> ans(n);

  vector <pair<int, int>> lowest;
  for (int i = n-1; i >= 0; i--) {
    while (!lowest.empty() && lowest.back().first >= p[i])
      lowest.pop_back();

    if (lowest.empty()) {
      ans[i] = n-1;
      lowest.push_back({p[i], i});
      continue;
    }

    pair <int, int> myp = {p[i] - c, -1};
    auto it = lower_bound(lowest.begin(), lowest.end(), myp);
    if (it == lowest.begin()) {
      ans[i] = n-1;
    } else {
      --it;
      ans[i] = it->second-1;
    }

    lowest.push_back({p[i], i});
  }

  for (int i : ans) cout << i << " ";
  cout << "\n";
}
