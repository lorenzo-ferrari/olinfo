#include <bits/stdc++.h>
using namespace std;

int presta(int n, int c, vector<int> p) {
  sort(p.begin(), p.end());
  int i = 0;
  while (c > 0) {
    c -= p[n - ++i];
  }
  return i;
}