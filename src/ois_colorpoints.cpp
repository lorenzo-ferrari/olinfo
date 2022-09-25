#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int INF = 1e9;

void compress(vector<int>& v, vector<int>& z) {
  z = v;
  sort(z.begin(), z.end());
  z.resize(unique(z.begin(), z.end()) - z.begin());
  for (int& i : v) i = lower_bound(z.begin(), z.end(), i) - z.begin();
}

int dfs(int n, const vector<vector<int>>& adj, const vector<vector<int>>& c, vector<int>& par) {
  fill(par.begin(), par.end(), -1);
  stack<array<int, 2>> st;
  st.push({0, INF});
  while (!st.empty()) {
    auto [v, flow] = st.top();
    st.pop();
    for (int u : adj[v]) {
      if (par[u] == -1 && c[v][u]) {
        int new_flow = min(flow, c[v][u]);
        par[u] = v;
        if (u == n-1) {
          return new_flow;
        }
        st.push({u, new_flow});
      }
    }
  }
  return 0;
}

int maxflow(int n, const vector<vector<int>>& adj, vector<vector<int>>& c) {
  int flow = 0;
  int new_flow = 0;
  vector<int> par(n);
  while ((new_flow = dfs(n, adj, c, par))) {
    flow += new_flow;
    int cur = n-1;
    while (cur != 0) {
      int prv = par[cur];
      c[prv][cur] -= new_flow;
      c[cur][prv] += new_flow;
      cur = prv;
    }
  }
  return flow;
}

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  vector<int> x(n), y(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> y[i];
  }
  vector<int> ox; compress(x, ox);
  vector<int> oy; compress(y, oy);
  vector<int> fx(n), fy(n);
  for (int i : x) ++fx[i];
  for (int i : y) ++fy[i];

  /* MAXFLOW */
  int nn = 2*n + 2;
  vector<vector<int>> adj(nn);
  vector<vector<int>> c(nn, vector<int>(nn, 0));
  auto add_edge = [&](int v, int u, int w) -> void {
    adj[v].push_back(u);
    adj[u].push_back(v);
    c[v][u] = w;
  };
  for (int i = 0; i < n; ++i) {
    add_edge(0, i+1, fx[i] / 3);
    add_edge(i+1+n, 2*n+1, fy[i] / 3);
    add_edge(x[i]+1, y[i]+1+n, 1);
  }
  int flow = maxflow(nn, adj, c);
  if (3 * flow != n) {
    cout << "No" << "\n";
  } else {
    cout << "Yes" << "\n";
    cout << flow << "\n";
    for (int i = 0; i < n; ++i) {
      if (c[x[i]+1][y[i]+1+n] == 0) {
        cout << ox[x[i]] << " " << oy[y[i]] << "\n";
      }
    }
  }
}