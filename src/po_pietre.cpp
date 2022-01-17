#include <bits/stdc++.h>
using namespace std;

int n;

int Confronta(int a, int b); // v[a] > v[b]
bool _less(int a, int b) { // red[a] < blue[b]
  if (a == 0 || b == n + 1) return true;
  if (b == 0 || a == n + 1) return false;
  return Confronta(n + b, a);
}
bool _greater(int a, int b) { // red[a] > blue[v]
  return !_less(a, b);
}


int Trova(int _n, int g) {
  ::n = _n;
  int rl = max(0, g - n);
  int rr = min(n, g) + 1;
  while (rr - rl > 1) {
    int rm = (rl + rr) / 2;
    if (_less(rm, g - rm + 1)) {
      rl = rm;
    } else {
      rr = rm;
    }
  }
  return _greater(rl, g - rl) ? rl : n + g - rl;
}
