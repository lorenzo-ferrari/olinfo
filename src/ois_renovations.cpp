#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 1e5 + 5;

int n, q, k;
int  t[2 * N];

void build(vector<int>& a) {
  for (int i = 0; i < n; ++i)
    t[i + n] = max(0, a[i] - k);
  for (int i = n - 1; i > 0; --i)
    t[i] = t[i << 1] + t[i << 1 | 1];
}

void update(int p, int v) {
  for (t[p += n] = max(0, v - k); p > 0; p >>= 1)
    t[p >> 1] = t[p] + t[p ^ 1];
}

int query(int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

LL mod = 1e9 + 7;
LL f[2300000];

LL fxp(LL x, LL y) {
  LL ans = 1;
  while (y) {
    if (y & 1)
      ans = ans * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return ans;
}

int choose(int N, int K) {
  // cout << N << " " << K << "\n";
  long long ans = 1;
  // K = max(K, N - K);
  ans = ans * f[N] % mod;
  ans = ans * fxp(f[K], mod-2) % mod;
  ans = ans * fxp(f[N-K], mod-2) % mod;
  return ans;
}

int main() {
  f[0] = 1;
  for (int i = 1; i < 2300000; ++i)
    f[i] = f[i - 1] * i % mod;
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  cin >> n >> q >> k;
  vector<int> a(n);
  for (int& i : a) cin >> i;
  build(a);
  for (int i = 0, ty; i < q; ++i) {
    cin >> ty;
    if (ty == 1) {
      int a, b;
      cin >> a >> b;
      update(a-1, b);
    } else {
      int l, r, s;
      cin >> l >> r >> s; --l;
      s -= k * (r - l) + query(l, r);
      if (s < 0) {
        cout << 0 << "\n";
      } else if (s == 0) {
        cout << 1 << "\n";
      } else {
        cout << choose(s+r-l-1, s) << "\n";
      }
    }
  }
}
