#include <bits/stdc++.h>
using namespace std;
using LL = long long;

bool examine(int x, int y);
void solution(int xc, int yc);

void find_centre(int n, int xi, int yi) {
  auto check = [&](int x, int y) {
    if (x <= 0 || y <= 0 || x > n || y > n) return false;
    return examine(x, y);
  };
  auto query = [&](LL delta, LL dir) {
    switch (dir) {
      case 0: return examine(xi, yi + delta);
      case 1: return examine(xi - delta, yi);
      case 2: return examine(xi, yi - delta);
      case 3: return examine(xi + delta, yi);
    }
    assert(false && "This should never be reached");
    return false;
  };
  auto bs = [&](LL l, LL r, LL dir) {
    bool redFound = false;
    while (r - l > 1) {
      LL mid = l + (r - l) / 2;
      if (query(mid, dir)) {
        if (redFound) {
          l = mid;
          continue;
        }
        bool half = query(mid / 2, dir);
        bool quarter = query(mid / 4, dir);
        if (!quarter) r = mid / 4;
        else if (!half) r = mid / 2;
        else l = mid;
        redFound = true;
      } else {
        r = mid;
      }
    }
    return l;
  };
  LL dw = bs(0, n + 1 - yi, 0);
  LL da = bs(0, xi,         1);
  LL ds = bs(0, yi,         2);
  LL dd = bs(0, n + 1 - xi, 3);
  assert(dw + ds == da + dd && "(Xi, Yi) should be in a square M x M");
  LL m = dw + ds + 1;
  LL xc = (xi-da + xi+dd) / 2;
  LL yc = (yi-ds + yi+dw) / 2;
  LL cw; for (cw = 0; check(xi, yi + 2 * m * (cw + 1)); ++cw);
  LL ca; for (ca = 0; check(xi - 2 * m * (ca + 1), yi); ++ca);
  LL cs; for (cs = 0; check(xi, yi - 2 * m * (cs + 1)); ++cs);
  LL cd; for (cd = 0; check(xi + 2 * m * (cd + 1), yi); ++cd);
  for (; cw > cs; --cw, ++cs, yc += 2 * m);
  for (; cw < cs; ++cw, --cs, yc -= 2 * m);
  for (; cd > ca; --cd, ++ca, xc += 2 * m);
  for (; cd < ca; ++cd, --ca, xc -= 2 * m);
  if (cw == cs) solution(xc, yc);
  else solution(xc + 2 * m, yc + 2 * m);
}
