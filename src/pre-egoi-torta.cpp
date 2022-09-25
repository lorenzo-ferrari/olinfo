#include <bits/stdc++.h>
using namespace std;
using LL = long long;

bool works(int k, LL tot, vector<int> b) {
  LL u = tot / k;
  LL a = 0, cnt = 0;
  for (int i : b) {
    a += i;
    if (a == tot / k) {
      ++cnt;
      a = 0;
    }
  }
  return cnt >= k;
}

int taglia(int n, vector<int> b) {
  LL tot = 0;
  for (int i : b) tot += i;
  vector<bool> p(n+1, true);
  for (int i = 2; i <= n; ++i) {
    if (p[i]) {
      for (int j = 2*i; j <= n; j += i) {
        p[j] = false;
      }
      if (tot % i == 0 && works(i, tot, b)) {
        return i;
      }
    }
  }
  return -1;
}