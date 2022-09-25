#include <bits/stdc++.h>
using namespace std;
using LL = long long;

array<int, 2> furthest(int v, int p, const vector<vector<array<int, 2>>>& adj) {
  array<int, 2> ans{0, v};
  for (auto [u, w] : adj[v]) {
    if (u == p) continue;
    auto sub = furthest(u, v, adj);
    if (ans[0] < sub[0] + w) {
      sub[0] += w;
      ans = sub;
    }
  }
  return ans;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n; cin >> n;
  vector<vector<array<int, 2>>> adj(n);
  for (int i = 0, a, b, c; i < n-1; ++i) {
    cin >> a >> b >> c; --a; --b;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }
  int v = furthest(0, -1, adj)[1];
  int w = furthest(v, -1, adj)[0];
  cout << w << "\n";
}
