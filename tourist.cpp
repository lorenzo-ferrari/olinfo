#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int GreatestHappiness(int n, int k, int h[]) {
  int f[1001] {};
  for (int i = 0; i < n; ++i)
    ++f[h[i]];

  int hp = 0;
  int gh = 0;
  int tk = 0;
  int pv = 0;
  int lh = 1000;
  for (int i = n - 1; i >= 0; --i) {
    //
    if (i != n - 1) {
      --f[h[i + 1]];
      if (f[h[i + 1]] == -1) {
        f[h[i + 1]] = 0;
        hp -= h[i + 1];
        while (lh > 0 && f[lh] <= 0)
          --lh;
        hp += lh;
        --f[lh];
      }
    }
    //

    tk = max(0, k - i);
    for (int i = 0; i < tk - pv; ++i) {
      while (lh > 0 && f[lh] <= 0)
        --lh;
      hp += lh;
      --f[lh];
    }

    gh = max(gh, hp);
    pv = tk;
  }

  return gh;
}