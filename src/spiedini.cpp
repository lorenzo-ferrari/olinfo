#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 20000001;

int solve(int n, int k, int v[]) {
  int p[N];
  p[0] = 0;
  int acc = 0;
  for (int i = 0; i < n; i++) {
    p[i + 1] = p[i] + (v[i] == 0);
    acc += v[i];
  }
  
  // si bugga a caso se li prendo tutti
  int a1 = 0;
  int a2 = 0;
  for (int i = 0; i < n && v[i]; i++)
    a1 += v[i];
  for (int i = n-1; i >= 0 && v[i]; i--)
    a2 += v[i];

  if (acc - a1 <= k || acc - a1 <= k)
    return p[n];
  //

  int ans = 0;
  int tk = k;
  int r = n - 1; // ultimo valore che non ho
  while (r >= 0 && tk > v[r])
    tk -= v[r--];
  ans = p[n] - p[r + 1];

  for (int i = 0; i < n; i++) {
    tk -= v[i];
    while (r < n-1 && tk < 0)
      tk += v[++r]; // togli i valori che ho
    ans = max(ans, p[i + 1] + p[n] - p[r + 1]);
    if (tk < 0)
      return ans;
  }

  return ans;
}