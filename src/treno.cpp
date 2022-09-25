#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const LL mod = 998244353;

vector<array<int, 2>> ans;

void solve(int n) {
  if (n == 3) {
    ans.push_back({2,7});
    ans.push_back({6,2});
    ans.push_back({4,6});
    ans.push_back({7,4});
  } else if (n == 4) {
    ans.push_back({4,9});
    ans.push_back({6,4});
    ans.push_back({2,6});
    ans.push_back({5,2});
    ans.push_back({9,5});
  } else {
    ans.push_back({n, 2*n+1});
    ans.push_back({2*n-1, n});
    solve(n-1);
    ans.push_back({2*n+1, 2*n-1});
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n; cin >> n;
  solve(n);
  cout << ans.size() << " " << n << "\n";
  for (auto& [a, b] : ans) {
    cout << a << " " << b << "\n";
  }
}
