#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int& i : a)
    cin >> i;
  if (n % 2 == 1) return false;
  if (k == 1) return true;
  vector<bool> v(n);
  vector<int> cnt(k + 1);
  stack<pair<int, int>> st;
  for (int i = 0; i < n; ++i) {
    if (st.empty()) {
      st.push({a[i], 0});
    } else if (st.top().first == a[i]) {
      st.pop();
    } else {
      st.push({a[i], 1});
    }
  }
  return st.empty();
}

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int t; cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }
}
