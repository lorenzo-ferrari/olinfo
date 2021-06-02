#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 1005;

int n;
int p[N];
int c[N][N];
bool r[N][N];
vector<int> g[N];

inline int dfs(int &s, int &e) {
  fill(p, p + 2*n+2, -1);

  stack<int> st;
  st.push(s);

  while (!st.empty()) {
    int v = st.top();
    st.pop();

    for (int &u : g[v]) {
      if (p[u] == -1 && c[v][u]) {
        p[u] = v;
        if (u == e)
          return 1;
        st.push(u);
      }
    }
  }

  return 0;
}

inline int maxflow(int s, int e) {
  int flow = 0;

  while (dfs(s, e)) {
    ++flow;
    int cur = e;
    while (cur != s) {
      int prv = p[cur];
      --c[prv][cur];
      ++c[cur][prv];
      cur = prv;
    }
  }

  return flow;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

  int d[N];
  for (int i = 0; i < n; i++)
    cin >> d[i];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int dist;
      cin >> dist;
      if (i != j && d[i] + dist <= d[j])
        r[i][j] = true;
    }
  }

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        r[i][j] = r[i][j] || (r[i][k] && r[k][j]);

  for (int i = 0; i < n; i++) {
    g[0].push_back(i+1);
    c[0][i+1] = 1;

    g[i+1+n].push_back(2*n+1);
    c[i+1+n][2*n+1] = 1;

    for (int j = 0; j < n; j++) {
      if (r[i][j]) {
        g[i+1].push_back(j+1+n);
        g[j+1+n].push_back(i+1);
        c[i+1][j+1+n] = 1;
      }
    }
  }

  cout << n - maxflow(0, 2*n+1) << "\n";
}