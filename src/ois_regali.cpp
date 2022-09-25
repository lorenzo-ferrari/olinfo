#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int solve(vector<int> idxs, int step, vector<vector<int>>& v, int q) {
  int n = idxs.size();
  if (n <= 1 || step >= q) return 0;
  map<int, vector<int>> mp;
  for (int i : idxs) {
    mp[v[i][step]].push_back(i);
  }
  int ans = 0;
  for (auto& x : mp) {
    if (x.second.size() >= 2) {
      ans = max(ans, 1 + solve(x.second, step+1, v, q));
    }
  }
  return ans;
};

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n; cin >> n;
  int q; cin >> q;
  vector<vector<int>> v(n, vector<int> (q));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < q; ++j) {
      cin >> v[i][j];
    }
  }
  vector<int> i(n);
  iota(i.begin(), i.end(), 0);
  cout << solve(i, 0, v, q) << "\n";
}
