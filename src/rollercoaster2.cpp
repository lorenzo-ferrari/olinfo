#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

inline int get_int() {
    int n = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

inline void print(int n) {
    int i = 0;
    char S[20];
    if (n == 0) {
        putchar_unlocked('0');
        putchar_unlocked(' ');
        return;
    }
    while (n) {
        S[i++] = n % 10 + '0';
        n /= 10;
    }
    while (--i >= 0)
        putchar_unlocked(S[i]);
    putchar_unlocked(' ');
}

#define SQ(a) (a)*(a)
#define N 500
#define H 2001

// 1: <
// 0: >
int32_t main() {
  int n = get_int();

  int h[N];
  for (int i = 0; i < n; i++)
    h[i] = get_int();

    int dp[N][H][2];
  for (int i = H-1; i >= 0; i--) {
    dp[n-1][i][1] = SQ(h[n-1] - i);
    dp[n-1][i][0] = SQ(h[n-1] - i);
  }

  for (int i = n-2, cmin; i >= 0; i--) {
    cmin = 1e9;
    for (int j = H-1; j >= 0; j--) {
      dp[i][j][1] = SQ(h[i] - j) + cmin;
      cmin = min(cmin, dp[i+1][j][0]);
    }
    cmin = 1e9;
    for (int j = 0; j < H; j++) {
      dp[i][j][0] = SQ(h[i] - j) + cmin;
      cmin = min(cmin, dp[i+1][j][1]);
    }
  }

  int ans = 1e9;
  for (int i = 0; i < H; i++)
    ans = min(ans, min(dp[0][i][0], dp[0][i][1]));

  print(ans);
}
