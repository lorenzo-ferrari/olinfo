// https://training.olinfo.it/#/task/salesman/statement
#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
using LL = long long;

class segment {
  int n;
  vector<LL> t;
public:
  segment(int _n, vector<LL> a) : n(_n) {
    t.resize(2 * n);
    for (int i = 0; i < n; ++i) t[i + n] = a[i];
    for (int i = n - 1; i > 0; --i) t[i] = max(t[i << 1], t[i << 1 | 1]);
  }
  void upd(LL i, LL val) {
    for (t[i += n] = val; i > 1; i >>= 1) t[i >> 1] = max(t[i], t[i ^ 1]);
  }
  LL rmq(int l, int r) {
    LL ans = -1e18;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = max(ans, t[l++]);
      if (r & 1) ans = max(ans, t[--r]);
    }
    return ans;
  }
};

const int N = 5e5 + 5;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  LL n, u, d, s;
  cin >> n >> u >> d >> s;
  swap(u, d);
  vector<LL> t(n), l(n), m(n);
  vector<vector<int>> time2id(N);
  for (int i = 0; i < n; ++i) {
    cin >> t[i] >> l[i] >> m[i];
    time2id[t[i]].push_back(i);
  }
  for (auto& x : time2id)
    sort(x.begin(), x.end(), [&](int i, int j){return l[i] < l[j];});
  auto dist = [&](LL a, LL b) {
    return a < b ? (b - a) * u : (a - b) * d;
  };
  vector<LL> dp(N); // dp[i] = maximum max profit starting in s and ending in i
  for (int i = 0; i < N; ++i) dp[i] = -dist(s, i);
  vector<LL> up(N);
  vector<LL> oldDp(N), newDp(N);
  vector<LL> down(N);
  for (int i = 0; i < N; ++i) up[i] = dp[i] + dist(0, i);
  for (int i = 0; i < N; ++i) down[i] = dp[i] + dist(N-1, i);
  segment st_up(N, up);
  segment st_down(N, down);
  auto upd = [&](LL i, LL v) {
    st_up.upd(i, v + dist(0, i));
    st_down.upd(i, v + dist(N-1, i));
  };
  for (int i = 0; i < N; ++i) {
    for (int j : time2id[i]) {
      oldDp[l[j]] = dp[l[j]];
      LL from_down = st_up.rmq(0, l[j]+1) - dist(0, l[j]) + m[j];
      LL from_up = st_down.rmq(l[j], N) - dist(N-1, l[j]) + m[j];
      dp[l[j]] = max(dp[l[j]], max(from_up, from_down));
      newDp[l[j]] = dp[l[j]];
      upd(l[j], dp[l[j]]);
    }
    for (int j : time2id[i]) {
      dp[l[j]] = oldDp[l[j]];
      upd(l[j], dp[l[j]]);
    }
    reverse(time2id[i].begin(), time2id[i].end());
    for (int j : time2id[i]) {
      LL from_down = st_up.rmq(0, l[j]+1) - dist(0, l[j]) + m[j];
      LL from_up = st_down.rmq(l[j], N) - dist(N-1, l[j]) + m[j];
      dp[l[j]] = max(dp[l[j]], max(from_up, from_down));
      newDp[l[j]] = max(newDp[l[j]], dp[l[j]]);
      upd(l[j], dp[l[j]]);
    }
    for (int j : time2id[i]) {
      dp[l[j]] = newDp[l[j]];
      upd(l[j], dp[l[j]]);
    }
  }
  for (int i = 0; i < N; ++i) dp[i] -= dist(i, s);
  cout << *max_element(dp.begin(), dp.end()) << "\n";
}
