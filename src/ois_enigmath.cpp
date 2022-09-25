#include <bits/stdc++.h>
using namespace std;

int s(int x) {
  int ans = 0;
  while (x) {
    ans += x % 10;
    x /= 10;
  }
  return ans;
}

int e(int x) {
  if (x < 10) return x;
  return x + e(s(x));
}

int main() {
  int emin; cin >> emin;
  int emax; cin >> emax;
  int n = emax - emin + 1;
  vector<vector<int>> ns(n);
  for (int x = max(0, emin - 200); x <= emax; ++x) {
    int val = e(x);
    if (emin <= val && val <= emax) {
      ns[val - emin].push_back(x);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (ns[i].size() == 0) cout << "IMPOSSIBLE\n";
    else if (ns[i].size() > 1) cout << "AMBIGUOUS\n";
    else cout << ns[i][0] << "\n";
  }
}
