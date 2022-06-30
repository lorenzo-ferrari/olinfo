#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct segment {
  int n;
  vector<int> t;
  segment(int n) : n(n) {
    t.assign(2 * n, 1e9);
  }
  void update(int i, int v) {
    for (t[i += n] = v; i > 1; i >>= 1) {
      t[i >> 1] = min(t[i], t[i^1]);
    }
  }
  int query(int l, int r) {
    r = min(r, n);
    l = min(l, r);
    int ans = 1e9;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = min(ans, t[l++]);
      if (r & 1) ans = min(ans, t[--r]);
    }
    return ans;
  }
};

int salta(int n, vector<int> s, vector<int> a, vector<int> b) {
  vector<int> dp(n);
  segment st(n+1);
  st.update(n, 0);
  for (int i = n-1; i >= 0; --i) {
    dp[i] = max(s[i], st.query(i + a[i], i + b[i] + 1));
    st.update(i, dp[i]);
  }
  return dp[0];
}
