#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize ("O3")
using LL = long long;

const int mod = 1e9 + 7;

double lg[100001];

struct fn {
  int b, c;
  fn() : b(1), c(0) {}
  fn(int _b, int _c) : b(_b), c(_c) {}

  int eval(LL i) {
    LL y = c, ans = 1;
    while (y) {
      if (y & 1)
        ans = ans * i % mod;
      i = i * i % mod;
      y >>= 1;
    }
    return ans * b % mod;
  }
};
bool cmp(int i, fn a, fn b) {
  return lg[a.b] + lg[i] * a.c < lg[b.b] + lg[i] * b.c;
}

struct segment {
  int n;
  vector<fn> st;
  segment(int _n) {
    for (n = 1; n < _n; n <<= 1);
    st.resize(2 * n);
  }

  void add_fn(int i, int l, int r, fn f) {
    int m = (l + r) / 2;
    bool lef = cmp(l, st[i], f);
    bool mid = cmp(m, st[i], f);
    if (mid)
      swap(st[i], f);
    if (r - l == 1)
      return;
    if (lef != mid)
      add_fn(2*i, l, m, f);
    else
      add_fn(2*i+1, m, r, f);
  }

  void upd(int i, int tl, int tr, int l, int r, fn f) {
    if (tr <= l || r <= tl) return;
    if (l <= tl && tr <= r)
      add_fn(i, tl, tr, f);
    else {
      upd(2*i,   tl, (tl+tr)/2, l, r, f);
      upd(2*i+1, (tl+tr)/2, tr, l, r, f);
    }
  }

  int qry(int i) {
    fn ans(1, 0);
    for (int p = i + n; p > 0; p >>= 1)
      if (cmp(i, ans, st[p]))
        ans = st[p];
    return ans.eval(i);
  }

  void update(int l, int r, int b, int c) {
    upd(1, 0, n, l, r, {b, c});
  }
};

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  for (int i = 1; i <= 100000; ++i)
    lg[i] = log(i);
  int n; cin >> n;
  segment st(n + 1);
  for (int i = 1, a; i <= n; ++i) {
    cin >> a;
    st.update(i, i+1, a, 0);
  }
  int q; cin >> q;
  for (int ty, x, y, b, c; q--;) {
    cin >> ty;
    if (ty == 1) {
      cin >> x;
      cout << st.qry(x) << "\n";
    } else {
      cin >> x >> y >> b >> c;
      st.update(x, y+1, b, c);
    }
  }
}
