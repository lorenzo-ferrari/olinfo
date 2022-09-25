#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

inline int get_int() {
  int n = 0;
  char c = getchar_unlocked();
  while ('0' <= c && c <= '9') {
    n = n * 10 + c - '0';
    c = getchar_unlocked();
  }
  return n;
}

constexpr size_t N = 1e6;

struct Segment {
  int n;
  int t[2 * N];
  Segment(int n) : n(n) {
    fill(t, t + 2*n, -1e9);
  }
  inline void upd(int i, int v) {
    for (t[i += n] = v; i > 1; i >>= 1) {
      t[i >> 1] = max(t[i], t[i ^ 1]);
    }
  }
  inline int query(int l, int r) {
    int ans = -1e9;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = max(ans, t[l++]);
      if (r & 1) ans = max(ans, t[--r]);
    }
    return ans;
  }
};

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n = get_int();
  array<int, 2> v[N];
  for (int i = 0; i < n; ++i) {
    v[i][0] = get_int();
    v[i][1] = i;
  }
  sort(v, v + n);
  Segment stp(n), stm(n);
  int ans = 0;
  for (int _ = 0; _ < n; ++_) {
    int s = v[_][0], i = v[_][1];
    ans = max(ans, stp.query(i, n) - i + s);
    ans = max(ans, stm.query(0, i) + i + s);
    stp.upd(i, +i-s);
    stm.upd(i, -i-s);
  }
  cout << ans << "\n";
}
