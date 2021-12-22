#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
using namespace std;

#define int uint64_t

const int N = 2e5;
const int mod = 1e9 + 7;

int fct[N + 1];
int i_fct[N + 1];

int choose(int _n, int _k) {
  return ((fct[_n] * i_fct[_k]) % mod) * i_fct[_n - _k] % mod;
}

int fexp(int x, int y) {
  int ans = 1;

  while (y) {
    if (y & 1)
      ans = (ans * x) % mod;
    x = (x * x) % mod;
    y >>= 1;
  }

  return ans;
}

void init() {
  fct[0] = 1, i_fct[0] = 1;
  for (int i = 1; i <= N; i++) {
    fct[i] = (i * fct[i - 1]) % mod;
    i_fct[i] = fexp(fct[i], mod - 2);
    assert((fct[i] * i_fct[i]) % mod == 1);
  }
}

int32_t main() {
  init();
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int k;
  cin >> k;

  vector <int> v(k);
  for (int &i : v)
    cin >> i;

  vector <vector<int>> ways(k, vector <int> (k));

  for (int i = 0; i < k; i++) {
    int val = i+1;
    for (int j = 0; j <= v[i]; j++) {
      ways[i][(val * j) % k] += choose(v[i], j);
      ways[i][(val * j) % k] %= mod;
    }
  }

  vector <int> dp(k), prv(k);
  prv[0] = 1;
  for (auto w : ways) {
    for (int i = 0; i < k; i++) {
      for (int j = 0; j < k; j++) {
        dp[(j + i) % k] += (w[i] * prv[j]) % mod;
        dp[(j + i) % k] %= mod;
      }
    }
    prv = dp;
    dp.assign(k, 0);
  }

  cout << prv[0] << "\n";
}
