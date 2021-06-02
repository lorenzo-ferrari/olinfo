#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int INF = 1e9;
int dfs(int n, int s, int e, vector<vector<int>> &c, vector<int> &par) {
  fill(par.begin(), par.end(), -1);

  stack<pair<int, int>> st;
  st.push({s, INF});
  while (!st.empty()) {
    int v = st.top().first;
    int flow = st.top().second;
    st.pop();

    for (int i = 0; i < n; i++) {
      if (c[v][i] && par[i] == -1) {
        int new_flow = min(flow, c[v][i]);
        par[i] = v;

        if (i == e)
          return new_flow;

        st.push({i, new_flow});
      }
    }
  }

  return 0;
}

int maxflow(int n, int s, int e, vector<vector<int>> &c) {
  vector<int> par(n);
  int flow = 0;
  int new_flow;

  while (new_flow = dfs(n, s, e, c, par)) {
    flow += new_flow;

    int cur = e;
    while (cur != s) {
      int prv = par[cur];

      c[prv][cur] -= new_flow;
      c[cur][prv] += new_flow;

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

  vector<vector<int>> c(n + 2, vector<int> (n + 2));

  for (int i = 1; i <= n; i++) cin >> c[0][i];
  for (int i = 1; i <= n; i++) cin >> c[i][n+1];

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> c[i][j];

  cout << maxflow(n+2, 0, n+1, c) << "\n";
}