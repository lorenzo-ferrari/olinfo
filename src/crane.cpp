#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
using LL = long long;

/*
0 \to D
i-th crane:
  position X_i
  arm R_i meter long
  move the head (with or without load) at cost K_i / meter
  rotating the arm by 180° at cost T_i
Initially all the heads are at maximal extension pointing to dir (0-1)
The cranes can be operated in increasing order of X
Compute minimum cost to move from 0 to D

1 <= D <= 50'000
1 <= N <= 500
0 <= X_i <= 100'000
1 <= R_i <= 500
0 <= T_i, K_i <= 100'000
X_i <= X_i+1

dp[crane_id][position]
implement as dp[position] and just process the cranes in inc. order
-> compute minimum transition to each position based on prv costs

dp[x] = right now, the load has been dropped at position x
*/

struct crane {
  int x, r, t, k, dir;
  crane() {}
};
istream& operator >>(istream& is, crane& a) {
  return is >> a.x >> a.r >> a.t >> a.k >> a.dir;
}

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  const int SHIFT = 1000;
  const int D = 100000 + 2 * SHIFT;
  int d; cin >> d;
  int n; cin >> n;
  vector<crane> cranes(n);
  for (crane& c : cranes) {
    cin >> c;
    c.x += SHIFT;
  }
  vector<LL> dp(D, 1e18);
  dp[SHIFT] = 0;

  auto cost = [](int i, int j, crane c) -> int {
    if (i < c.x && j < c.x && i < j) return c.k*(j-(c.x-c.r)) + c.t*(c.dir == 1);
    if (i < c.x && j < c.x && j < i) return c.k*(i-(c.x-c.r)+(i-j)) + c.t * (c.dir == 1);
    if (i > c.x && j > c.x && j < i) return c.k*((c.x+c.r)-j) + c.t*(c.dir == 0);
    if (i > c.x && j > c.x && i < j) return c.k*((c.x+c.r)-i+(j-i)) + c.t*(c.dir == 0);
    if (i < c.x && j > c.x) return c.k*(i-(c.x-c.r) + abs((c.x-i)-(j-c.x))) + c.t*(1 + (c.dir == 1));
    if (i > c.x && j < c.x) return c.k*((c.x+c.r)-i + abs((i-c.x)-(c.x-j))) + c.t*(1 + (c.dir == 0));
    if (i == j) return 0;
    return -1;
  };

  // total time complexity: O(N R^2)
  for (crane& c : cranes) {
    // a) from sx to sx (up & down) O(R)
    // b) from sx to dx O(R^2), optimizable (segtree)
    // c) from dx to sx ^^
    // d) from dx to dx (up and down) O(R)
    // -> might as well do everything in O(R^2)
    for (int i = c.x-c.r; i <= c.x+c.r; ++i) {
      for (int j = c.x-c.r; j <= c.x+c.r; ++j) {
        if (i == c.x || j == c.x || dp[j] <= dp[i]) continue;
        dp[j] = min(dp[j], dp[i] + cost(i, j, c));
      }
    }
  }
  cout << dp[d + SHIFT] << "\n";
}
