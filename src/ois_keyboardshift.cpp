#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string layout = "qwertyuiopasdfghjklzxcvbnm";
  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    char c; cin >> c;
    auto it = find(layout.begin(), layout.end(), c);
    ++it;
    cout << *it;
  }
  cout << "\n";
}
