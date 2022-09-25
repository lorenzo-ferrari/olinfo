#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define all(x) x.begin(), x.end()

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  LL n; cin >> n;
  LL k; cin >> k;
  vector<LL> v(n + 1);
  for (int i = 1; i <= n; ++i) cin >> v[i];
  for (int i = 1; i <= n; ++i) v[i] += v[i - 1];
  auto cnt = [&](LL x) {
    // return how many tours with cost <= x
    // prf[e] - prf[s - 1] <= x
    LL ans = 0;
    for (int i = 1; i <= n; ++i) {
      // prf[s - 1] >= prf[i] - x
      ans += i - (lower_bound(all(v), v[i] - x) - v.begin());
    }
    return ans;
  };
  LL l = 0, r = 1e15;
  while (r - l > 1) {
    LL m = (r + l) / 2;
    if (cnt(m) < k)
      l = m;
    else
      r = m;
  }
  LL cost = l + 1;
  LL missing = k - cnt(cost - 1);
  for (int i = 0; i < n; ++i) {
    auto it = lower_bound(all(v), v[i] + cost);
    missing -= (it != v.end() && *it == v[i] + cost);
    if (!missing) {
      cout << i << " " << (it - v.begin() - 1) << "\n";
      return 0;
    }
  }
}
