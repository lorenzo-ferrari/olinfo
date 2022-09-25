#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
using ll = long long;

int n;
vector<int> c;
vector<int> p;
vector<vector<int>> adj;

struct emap {
  int mx = 0;
  int cnt = 0;
  unordered_map<int, int> fc;
  int size() { return fc.size(); }
  void add(int x, int mult = 1) {
    int prv = fc[x];
    fc[x] = prv + mult;
    if (prv + mult > mx) {
      mx = prv + mult;
      cnt = 1;
    } else if (prv + mult == mx) {
      ++cnt;
    }
  }
  int getans() { return cnt; }
};

int ANS = 0;

emap dfs(int v) {
  emap ans;
  ans.add(c[v]);
  for (int u : adj[v]) {
    emap tmp = dfs(u);
    if (tmp.size() > ans.size())
      swap(ans, tmp);
    for (const auto& pp : tmp.fc) {
      ans.add(pp.first, pp.second);
    }
  }
  ANS = max(ANS, ans.getans());

  return ans;
}

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  cin >> n;
  c.resize(n);
  p.resize(n);
  adj.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
  }
  p[0] = -1;
  for (int i = 1; i < n; ++i) {
    cin >> p[i];
    adj[p[i]].push_back(i);
  }
  dfs(0);
  cout << ANS << "\n";
}
