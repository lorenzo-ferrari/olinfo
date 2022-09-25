#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL aggiorna(int n, vector<int> a, vector<int> b) {
  LL ans = 0;
  for (int i = n - 2; i >= 0; --i) {
    ans += (a[i + 1] - a[i]) / b[i];
    a[i] += (a[i + 1] - a[i]) / b[i] * b[i];
  }
  return ans;
}
