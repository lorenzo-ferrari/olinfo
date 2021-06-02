#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int64_t N = 1e5 + 42;

uint64_t _n;
uint64_t conv[N];
uint64_t t_xor[2 * N];
uint64_t checkxor[N];

int64_t xor_query(int l, int r) {
  int64_t ans = 0;
  for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans ^= t_xor[l++];
    if (r & 1) ans ^= t_xor[--r];
  }
  return ans;
}

void modifica(int p, int val) {
  for (t_xor[p += _n] = conv[val]; p > 1; p >>= 1)
    t_xor[p >> 1] = t_xor[p] ^ t_xor[p ^ 1];
}

void inizio(int n, int m, int sfere[]) {
  _n = n;

	for (int i = 1; i <= n; i++)
		conv[i] = rand();

  checkxor[0] = 0;
  for (int i = 1; i <= n; i++)
    checkxor[i] = conv[i] ^ checkxor[i - 1];

  for (int i = 0; i < n; i++)
    t_xor[i + n] = conv[sfere[i]];

  for (int i = _n - 1; i > 0; i--)
    t_xor[i] = t_xor[i << 1] ^ t_xor[i << 1 | 1];
}

bool verifica(int l, int r) {
  return xor_query(l, r + 1) == checkxor[r-l+1];
}