// point = edge from set X to set Y
// -> minimum vertex cover in a bipartite graph G
// -> maximum matching in G
// -> maximum flow

#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize("Ofast")
using namespace std;

vector <vector<int>> g;
vector <vector<bool>> c;

inline bool dfs(int &s, int &e, vector <int> &par) {
  fill(par.begin(), par.end(), -1);
  stack <int> st;
  st.push(s);

  while (!st.empty()) {
    int v = st.top();
    st.pop();

    for (int &u : g[v]) {
      if (par[u] == -1 && c[v][u]) {
        par[u] = v;
        if (u == e)
          return 1;
        st.push(u);
      }
    }
  }

  return 0;
}

inline int maxflow(int n, int s, int e) {
  int flow = 0;
  vector <int> par(n);

  while (dfs(s, e, par)) {
    flow++;
    int cur = e;
    while (cur != s) {
      int prv = par[cur];
      c[cur][prv] = 1;
      c[prv][cur] = 0;
      cur = prv;
    }
  }

  return flow;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  int tot = 2*n + 2;
  g.resize(tot);
  c.assign(tot, vector <bool> (tot));

  for (int i = 0, x, y; i < n; i++) {
    cin >> x >> y;
    g[x].push_back(y + n);
    g[y + n].push_back(x);
    c[x][y + n] = 1;

    g[0].push_back(x);
    c[0][x] = 1;

    g[y + n].push_back(tot-1);
    c[y + n][tot-1] = 1;
  }

  cout << maxflow(tot, 0, tot-1) << "\n";
}
