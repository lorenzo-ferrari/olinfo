#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
using LL = long long;

#ifdef LORENZO
constexpr int LOG = 10;
#else
constexpr int LOG = 12;
#endif
constexpr int N = 1 << (2 * LOG);
constexpr int INF = 100;

int8_t d[2*N]; // avoid overflow: N^(N-1) ~ 2N

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int m; cin >> m;
  fill(d, d+N, INF);
  vector<vector<int>> dd(2*LOG);
  vector<vector<array<int, 3>>> jj(2*LOG);
  auto combine = [&](int a, int b, int w) -> void {
    if (d[a+b]>w) { d[a+b] = w; dd[w].push_back(a+b); jj[w].push_back({a, b, 0}); }
    if ((LL)a*b < N && d[a*b]>w) { d[a*b] = w; dd[w].push_back(a*b); jj[w].push_back({a, b, 1}); }
    if (a>b && a-b && d[a-b]>w) { d[a-b] = w; dd[w].push_back(a-b); jj[w].push_back({a, b, 2}); }
    if (a/b && d[a/b]>w) { d[a/b] = w; dd[w].push_back(a/b); jj[w].push_back({a, b, 3}); }
    if (a%b && d[a%b]>w) { d[a%b] = w; dd[w].push_back(a%b); jj[w].push_back({a, b, 4}); }
    if (a&b && d[a&b]>w) { d[a&b] = w; dd[w].push_back(a&b); jj[w].push_back({a, b, 5}); }
    if (a|b && d[a|b]>w) { d[a|b] = w; dd[w].push_back(a|b); jj[w].push_back({a, b, 6}); }
    if (a^b && d[a^b]>w) { d[a^b] = w; dd[w].push_back(a^b); jj[w].push_back({a, b, 7}); }
    if (b<2*LOG && (a>>b) && d[a>>b]>w) { d[a>>b] = w; dd[w].push_back(a>>b); jj[w].push_back({a, b, 8}); }
    if (b<2*LOG && (LL(a) << b) < N && d[a<<b]>w) { d[a<<b] = w; dd[w].push_back(a<<b); jj[w].push_back({a, b, 9}); }
  };
  dd[0].push_back(1); d[0] = 0;
  for (int w = 1; w < 2*LOG; ++w) {
    if (d[m] != INF) break;
    for (int a = 0; a < w; ++a) {
      for (int i : dd[a]) for (int j : dd[w-1-a]) {
        combine(i, j, w);
      }
    }
  }
  auto ots = [](int op) -> string {
    switch(op) {
      case 0: return "+";
      case 1: return "*";
      case 2: return "-";
      case 3: return "/";
      case 4: return "%";
      case 5: return "&";
      case 6: return "|";
      case 7: return "^";
      case 8: return ">>";
      case 9: return "<<";
      default: assert(false);
    }
    return " <sus> ";
  };
  while (d[m] == INF) continue;
  function<string(int)> restore = [&](int n) -> string {
    if (n == 1) return "1";
    int i = d[n];
    int j = find(dd[i].begin(), dd[i].end(), n) - dd[i].begin();
    int a = jj[i][j][0];
    int b = jj[i][j][1];
    int op = jj[i][j][2];
    return "(" + restore(a) + ")" + ots(op) + "(" + restore(b) + ")";
  };
  cout << restore(m) << "\n";
}