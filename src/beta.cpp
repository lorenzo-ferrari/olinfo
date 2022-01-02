#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n; cin >> n;
  map<int, int> frq;
  for (int i = 0, v; i < n; ++i) {
    cin >> v;
    ++frq[v];
  }
  int cnt = 0;
  for (auto [a, b] : frq)
    cnt += b >= 2;
  cout << (cnt <= 1 ? "NO" : "YES") << "\n";
}
