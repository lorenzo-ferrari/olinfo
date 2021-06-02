#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define F first
#define S second

const int64_t INF = 1e13;
void solve(int n, int m) {
  vector <vector <pair<int64_t, int64_t>>> g(n);
  for (int i = 0, a, b, c; i < m; i++) {
    cin >> a >> b >> c;
    #ifdef EVAL
      a--, b--;
    #endif
    g[a].push_back({b, c});
    g[b].push_back({a, c});
  }

  int64_t ans = 0;

  vector <bool> vis(n);
  vector <int64_t> d(n, INF);
  vector <int64_t> p(n, -1);

  priority_queue <pair<int64_t, int64_t>> Q;
  Q.push({0, 0});
  d[0] = 0;

  while (!Q.empty()) {
    int64_t v = Q.top().second;
    Q.pop();

    vis[v] = true;

    for (auto e : g[v]) {
      if (!vis[e.F] && d[e.F] > e.S) {
        d[e.F] = e.S;
        p[e.F] = v;
        Q.push({-e.S, e.F});
      }
    }
  }

  vector <pair<int64_t, int64_t>> e;

  for (int i = 1; i < n; i++) {
    ans += d[i];
    if (i < p[i]) {
      e.push_back({i, p[i]});
    } else {
      e.push_back({p[i], i});
    }
  }

  sort(e.begin(), e.end());

  if (ans >= INF) {
    cout << "Impossible" << "\n";
  } else {
    cout << ans << "\n";
    for (auto ed : e) {
      #ifdef EVAL
        ed.F++, ed.S++;
      #endif
      cout << ed.F << " " << ed.S << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  #ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "r", stdout);
  #endif

  int n, m;
  while (cin >> n >> m) {
    if (n == 0 && m == 0)
      break;
    solve(n, m);
  }
}
