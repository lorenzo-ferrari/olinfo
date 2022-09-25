#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 5001;

int p[N];

int findset(int i) {
  return p[i] == i ? i : p[i] = findset(p[i]);
}

void unionset(int a, int b) {
  a = findset(a);
  b = findset(b);
  p[b] = a;
}

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  int k; cin >> k;
  vector<int> pp(n);
  for (int i = 0; i < n; ++i) cin >> pp[i];
  for (int i = 0; i < n; ++i) p[i] = i;
  vector<int> l(k);
  for (int i = 0; i < k; ++i) {
    cin >> l[i];
    for (int j = 0; j < n-l[i]; ++j) {
    unionset(j, j+l[i]);
    }
  }
  vector<vector<int>> idx(n);
  vector<vector<int>> val(n);
  for (int i = 0; i < n; ++i) {
    int s = findset(i);
    idx[s].push_back(i);
    val[s].push_back(pp[i]);
  }
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    sort(val[i].begin(), val[i].end());
    sort(idx[i].begin(), idx[i].end());
    for (int j = 0; j < int(val[i].size()); ++j) {
      ans[idx[i][j]] = val[i][j];
    }
  }
  for (int i : ans) cout << i << " ";
  cout << "\n";
}
