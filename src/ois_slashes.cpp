#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
	int n; cin >> n;
	int m; cin >> m;
	vector<vector<bool>> g(n, vector<bool>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char c; cin >> c;
			g[i][j] = (c == '/');
		}
	}
  int nn = 2*n*m + n + m;
  vector<vector<int>> adj(nn);
  auto pos_to_idx = [&](int i, int j, char dir) -> int {
    if (dir == 'w') return i*(2*m+1) + j;
    if (dir == 's') return (i+1)*(2*m+1) + j;
    if (dir == 'a') return i*(2*m+1) + m + j;
    if (dir == 'd') return i*(2*m+1) + m + j + 1;
    return -1;
  };
  auto add_edge = [&](int a, int b) -> void {
    adj[a].push_back(b);
    adj[b].push_back(a);
  };
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    int w = pos_to_idx(i, j, 'w');
    int a = pos_to_idx(i, j, 'a');
    int s = pos_to_idx(i, j, 's');
    int d = pos_to_idx(i, j, 'd');
    if (g[i][j]) {
      add_edge(w, a);
      add_edge(s, d);
    } else {
      add_edge(w, d);
      add_edge(s, a);
    }
  }
  int ans = 0;
  vector<bool> vis(nn);
  for (int i = 0; i < nn; ++i) {
    if (!vis[i]) {
      ++ans;
      vis[i] = true;
      queue<int> Q; Q.push(i);
      while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int u : adj[v]) {
          if (vis[u]) continue;
          vis[u] = true;
          Q.push(u);
        }
      }
    }
  }
  cout << ans << "\n";
}
