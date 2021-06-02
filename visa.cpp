#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  const int N = 1000;
  const int INF = 1e9;

  int n;
  cin >> n;

  vector<int> v(n);
  vector<bitset<N>> e(n);
  vector<vector<pair<int, int>>> g(n);

  for (int i = 0, k, l; i < n; i++) {
    cin >> v[i] >> k >> l;
    for (int j = 0, ei; j < k; j++) {
      cin >> ei;
      e[i][ei] = 1;
    }

    for (int j = 0, c; j < l; j++) {
      cin >> c;
      g[i].push_back({c, 0});
    }

    for (int j = 0, t; j < l; j++) {
      cin >> t;
      g[i][j].second = t;
    }
  }

  // cerr << "INPUT PRESO" << endl;


  vector<vector<int>> d(n, vector<int> (n, INF));
  vector<vector<bool>> vis(n, vector<bool> (n));
  vector<vector<bitset<N>>> visti(n, vector<bitset<N>> (n));

  vector<vector<pair<int, int>>> tr(n, vector<pair<int, int>> (n));

  priority_queue<array<int, 3>> Q; // {dist, vertex, vertexYouMustHave}
  for (int i = 0; i < n; i++) {
    if (e[0][i]) {
      d[0][i] = 0;
      visti[0][i] = e[0];
      Q.push({0, 0, i});
    }
  }

  while (!Q.empty()) {
    int dist = -Q.top()[0];
    int cur  =  Q.top()[1];
    int m  = Q.top()[2];
    Q.pop();

    if (vis[cur][m])
      continue;
    vis[cur][m] = true;

    for (auto &[u, w] : g[cur]) {
      if (visti[cur][m][u]) {
      int nxtdist = dist + w + v[u];
      bitset<1000> nxtvisti = visti[cur][m] | e[u];
        for (int i = 0; i < n; i++) {
          if (nxtvisti[i] && d[u][i] > nxtdist) {
            d[u][i] = nxtdist;
            visti[u][i] = nxtvisti;

            Q.push({-d[u][i], u, i});

            tr[u][i] = {cur, m};
            // cout << "cur=" << cur << ",m=" << m << " -> u=" << u << ", i=" << i << endl;
          }
        }
      }
    }
  }

  int id = 0;
  for (int i = 0; i < n; i++)
    if (d[n-1][i] < d[n-1][id])
      id = i;

  pair<int, int> cur = {n-1, id};
  stack<int> ans;

  while (cur.first != 0) {
    ans.push(cur.first);
    cur = tr[cur.first][cur.second];
  }
  ans.push(0);

  cout << ans.size() << endl;
  while (!ans.empty()) {
    cout << ans.top() << " ";
    ans.pop();
  }
  cout << endl;
}
