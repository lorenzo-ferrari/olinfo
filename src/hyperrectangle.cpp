#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
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

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n = get_int();
  // cin >> n;
  vector <int> v(2*n);
  for (int &i : v)
    // cin >> i;
    i = get_int();

  sort(v.begin(), v.end());

  // sort(v.begin(), v.begin() + n);
  // sort(v.begin() + n, v.end());

  for (int i = 0; i < n; i++) {
    // cout << v[i] << " ";
    print(v[i]);
  }
  // cout << "\n";
  putchar_unlocked('\n');
  for (int i = n; i < 2*n; i++) {
    // cout << v[i] << " ";
    print(v[i]);
  }
  // cout << "\n";
}
