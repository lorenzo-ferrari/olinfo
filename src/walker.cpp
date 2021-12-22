// f(x) = n-1 ^ x - f(x-1)
// serie geometrica!
// -> formula chiusa per somma

#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define int int64_t

const int mod = 666013;

uint64_t fxp(uint64_t x, uint64_t y) {
    uint64_t ans = 1;

    while (y) {
        if (y & 1)
            ans = (ans * x) % mod;
        x = (x * x) % mod;
        y >>= 1;
    }

    return ans;
}

int64_t n, k;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> k;

  int a1 = (n-1) % mod;
  if (k & 1)
    a1 = (mod - a1) % mod;

  // r = -(n-1) % k
  int R = ((-n + 1) % mod + mod) % mod;

  int invden = fxp((1 + n - 1) % mod, mod-2);

  int RtoN = fxp(R, k-1);

  int ans = a1 * ((1 - RtoN + mod) % mod) % mod;
  ans = ans * invden % mod;

  cout << ans << "\n";
}
