#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int n;
int m;
int64_t sum;
int t[100000];

inline int query(int l, int r) {
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res = max(res, t[l++]);
    if (r & 1) res = max(res, t[--r]);
  }

  return res;
}

int Cambia(int p, int v) {
  sum += v - t[p + n];
  for (t[p += n] = v; p > 1; p >>= 1)
    t[p >> 1] = max(t[p], t[p ^ 1]);

  return !(sum % m) && query(0, n) <= sum / m;
}

void Inizializza(int _n, int _m, int _h[]) {
  n = _n;
  m = _m;
  while (_n--)
    sum += t[_n + n] = _h[_n];

  for (int i = n - 1; i > 0; --i)
    t[i] = max(t[i << 1], t[i << 1 | 1]);
}