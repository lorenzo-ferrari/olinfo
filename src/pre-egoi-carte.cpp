#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int scarta(int n, vector<bool> L, vector<bool> D, vector<bool> N) {
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int v = 0;
    v += L[i];
    v += D[i];
    v += N[i];
    ans += (v != 1);
  }
  return ans;
}
