#include <bits/stdc++.h>
using namespace std;
using LL = long long;

vector<LL> calcola(int t, int m, vector<LL> s, vector<LL> p) {
  vector<LL> ans(m);
  vector<array<LL, 2>> v(m);
  for (int i = 0; i < m; ++i) {
    v[i] = {p[i], i};
  }
  vector<array<LL, 2>> o(t);
  for (int i = 0; i < t; ++i) {
    o[i] = {i, s[i]};
  }
  sort(o.begin(), o.end());
  sort(v.begin(), v.end());
  array<LL, 2> tt{0, 0};  // {weight, number};
  array<LL, 2> cc{0, 0};  // {cur_id, how many taken};
  for (auto [w, i] : v) {
    while (cc[0] != t && tt[0] + o[cc[0]][0] * (o[cc[0]][1] - cc[1]) <= w) {
      tt[0] += o[cc[0]][0] * (o[cc[0]][1] - cc[1]);
      tt[1] += o[cc[0]][1] - cc[1];
      ++cc[0];
      cc[1] = 0;
    }
    if (cc[0] != t) {
      LL fr = w - tt[0];
      LL pr = fr / o[cc[0]][0];
      assert(pr < o[cc[0]][1] - cc[1]);
      tt[0] += o[cc[0]][0] * pr;
      tt[1] += pr;
      cc[1] += pr;
    }
    ans[i] = tt[1];
  }
  return ans;
}
