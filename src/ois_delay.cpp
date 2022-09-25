#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")

inline void print(int n) {
  if (n < 0) {
    putchar_unlocked('-');
    n = -n;
  }
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

int32_t main() {
  int n;
  scanf("%d", &n);
  int s[100000];
  for (int i = 0; i < n; ++i)
    scanf("%d", s + i);

  for (int i = 0, idx = 0, d; i < n; ++i) {
    scanf("%d", &d);
    if (idx < i - d)
          idx = i - d;
    print(s[idx]);
  }
}
