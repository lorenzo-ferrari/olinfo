#include <cmath>
#include <vector>
#include <limits>
#include <iostream>
#pragma GCC optimize ("03")
using namespace std;
#define int int64_t

inline int get_int() {
    int n = 0;
    char c = getchar_unlocked();
    bool meno = false;
    if (c == '-') {
      c = getchar_unlocked();
      meno = true;
    }
    while (c >= '0') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    return (meno) ? -n : n;
}

inline void print(int n) {
    if (n < 0) {
        putchar_unlocked('-');
        n = -n;
    }
    int i = 0;
    char S[20];
    if (n == 0) {
        putchar_unlocked('0');
        putchar_unlocked('\n');
        return;
    }
    while (n) {
        S[i++] = n % 10 + '0';
        n /= 10;
    }
    while (--i >= 0)
        putchar_unlocked(S[i]);
    putchar_unlocked('\n');
}

const int N = 2e5 + 42;
const int INF = numeric_limits<int64_t>::max();

int n, i0 = 0;
int a[N], ord[N];
int dp[N][2];
vector <int> t[N], g[N];

void dfs(int v, int par) {
  for (int i : g[v]) {
    if (i == par) continue;
    t[v].push_back(i);
    dfs(i, v);
  }
  ord[i0++] = v;
}

int32_t main() {
  int n = get_int();

  for (int i = 1, u, v; i < n; i++) {
    u = get_int(); v = get_int();
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs(0, -1);

  for (int i = 0; i < n; i++)
    a[i] = get_int();

  for (int i = 0, v; i < i0; i++) {
    v = ord[i];
    if (t[v].empty()) {
      dp[v][0] = a[v];
      dp[v][1] = 0;
    }
    else {
      int ans = 0, diff = INF, p = 0;
      for (int u : t[v]) {
        if (dp[u][0] > dp[u][1]) {
          ans += dp[u][0];
          diff = min(diff, dp[u][0] - dp[u][1]);
        }
        else {
          ans += dp[u][1];
          diff = min(diff, dp[u][1] - dp[u][0]);
          p ^= 1;
        }
      }
      dp[v][p] = ans + (p == 0) * a[v];
      dp[v][p ^ 1] = ans - diff + (p == 1) * a[v];
    }
  }

  print(max(dp[0][0], dp[0][1]));
}
